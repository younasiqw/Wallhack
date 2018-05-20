#include "ReflectiveLoader.h"
HINSTANCE hAppInstance = NULL;
//===============================================================================================//
#pragma intrinsic( _ReturnAddress )
__declspec(noinline) ULONG_PTR caller( VOID ) { return (ULONG_PTR)_ReturnAddress(); }

//[junk_enable /]

#define REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN

#ifdef REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR
DLLEXPORT ULONG_PTR WINAPI ReflectiveLoader( LPVOID lpParameter )
#else
DLLEXPORT ULONG_PTR WINAPI ReflectiveLoader( VOID )
#endif
{
	// the functions we need
	LOADLIBRARYA pLoadLibraryA     = NULL;
	GETPROCADDRESS pGetProcAddress = NULL;
	VIRTUALALLOC pVirtualAlloc     = NULL;
	NTFLUSHINSTRUCTIONCACHE pNtFlushInstructionCache = NULL;

	USHORT usCounter;

	// the initial location of this image in memory
	ULONG_PTR uiLibraryAddress;
	// the kernels base address and later this images newly loaded base address
	ULONG_PTR uiBaseAddress;

	// variables for processing the kernels export table
	ULONG_PTR uiAddressArray;
	ULONG_PTR uiNameArray;
	ULONG_PTR uiExportDir;
	ULONG_PTR uiNameOrdinals;
	DWORD dwHashValue;

	// variables for loading this image
	ULONG_PTR uiHeaderValue;
	ULONG_PTR uiValueA;
	ULONG_PTR uiValueB;
	ULONG_PTR uiValueC;
	ULONG_PTR uiValueD;
	ULONG_PTR uiValueE;

	// STEP 0: calculate our images current base address

	// we will start searching backwards from our callers return address.
	uiLibraryAddress = caller();

	// loop through memory backwards searching for our images base address
	// we dont need SEH style search as we shouldnt generate any access violations with this
	while( TRUE )
	{
		if( ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_magic == IMAGE_DOS_SIGNATURE )
		{
			uiHeaderValue = ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;
			// some x64 dll's can trigger a bogus signature (IMAGE_DOS_SIGNATURE == 'POP r10'),
			// we sanity check the e_lfanew with an upper threshold value of 1024 to avoid problems.
			if( uiHeaderValue >= sizeof(IMAGE_DOS_HEADER) && uiHeaderValue < 1024 )
			{
				uiHeaderValue += uiLibraryAddress;
				// break if we have found a valid MZ/PE header
				if( ((PIMAGE_NT_HEADERS)uiHeaderValue)->Signature == IMAGE_NT_SIGNATURE )
					break;
			}
		}
		uiLibraryAddress--;
	}

	// STEP 1: process the kernels exports for the functions our loader needs...

	// get the Process Enviroment Block
#ifdef WIN_X64
	uiBaseAddress = __readgsqword( 0x60 );
#else
#ifdef WIN_X86
	uiBaseAddress = __readfsdword( 0x30 );
#else WIN_ARM
	//uiBaseAddress = *(DWORD *)( (BYTE *)_MoveFromCoprocessor( 15, 0, 13, 0, 2 ) + 0x30 );
#endif
#endif

	// get the processes loaded modules. ref: http://msdn.microsoft.com/en-us/library/aa813708(VS.85).aspx
	uiBaseAddress = (ULONG_PTR)((_PPEB)uiBaseAddress)->pLdr;

	// get the first entry of the InMemoryOrder module list
	uiValueA = (ULONG_PTR)((PPEB_LDR_DATA)uiBaseAddress)->InMemoryOrderModuleList.Flink;
	while( uiValueA )
	{
		// get pointer to current modules name (unicode string)
		uiValueB = (ULONG_PTR)((PLDR_DATA_TABLE_ENTRY)uiValueA)->BaseDllName.pBuffer;
		// set bCounter to the length for the loop
		usCounter = ((PLDR_DATA_TABLE_ENTRY)uiValueA)->BaseDllName.Length;
		// clear uiValueC which will store the hash of the module name
		uiValueC = 0;

		// compute the hash of the module name...
		do
		{
			uiValueC = ror( (DWORD)uiValueC );
			// normalize to uppercase if the madule name is in lowercase
			if( *((BYTE *)uiValueB) >= 'a' )
			{
				uiValueC += *((BYTE *)uiValueB) - 0x20;
			}
			else
			{
				uiValueC += *((BYTE *)uiValueB);
			}
			uiValueB++;
		} while( --usCounter );

		// compare the hash with that of kernel32.dll
		if( (DWORD)uiValueC == KERNEL32DLL_HASH )
		{
			// get this modules base address
			uiBaseAddress = (ULONG_PTR)((PLDR_DATA_TABLE_ENTRY)uiValueA)->DllBase;

			// get the VA of the modules NT Header
			uiExportDir = uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew;

			// uiNameArray = the address of the modules export directory entry
			uiNameArray = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];

			// get the VA of the export directory
			uiExportDir = ( uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress );

			// get the VA for the array of name pointers
			uiNameArray = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfNames );
			
			// get the VA for the array of name ordinals
			uiNameOrdinals = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfNameOrdinals );

			usCounter = 3;

			// loop while we still have imports to find
			while( usCounter > 0 )
			{
				// compute the hash values for this function name
				dwHashValue = hash( (char *)( uiBaseAddress + DEREF_32( uiNameArray ) )  );
				
				// if we have found a function we want we get its virtual address
				if( dwHashValue == LOADLIBRARYA_HASH || dwHashValue == GETPROCADDRESS_HASH || dwHashValue == VIRTUALALLOC_HASH )
				{
					// get the VA for the array of addresses
					uiAddressArray = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfFunctions );

					// use this functions name ordinal as an index into the array of name pointers
					uiAddressArray += ( DEREF_16( uiNameOrdinals ) * sizeof(DWORD) );

					// store this functions VA
					if( dwHashValue == LOADLIBRARYA_HASH )
					{
						pLoadLibraryA = (LOADLIBRARYA)( uiBaseAddress + DEREF_32( uiAddressArray ) );
					}
					else if( dwHashValue == GETPROCADDRESS_HASH )
					{
						pGetProcAddress = (GETPROCADDRESS)( uiBaseAddress + DEREF_32( uiAddressArray ) );
					}
					else if( dwHashValue == VIRTUALALLOC_HASH )
						pVirtualAlloc = (VIRTUALALLOC)( uiBaseAddress + DEREF_32( uiAddressArray ) );
			
					// decrement our counter
					usCounter--;
				}

				// get the next exported function name
				uiNameArray += sizeof(DWORD);

				// get the next exported function name ordinal
				uiNameOrdinals += sizeof(WORD);
			}
		}
		else if( (DWORD)uiValueC == NTDLLDLL_HASH )
		{
			// get this modules base address
			uiBaseAddress = (ULONG_PTR)((PLDR_DATA_TABLE_ENTRY)uiValueA)->DllBase;

			// get the VA of the modules NT Header
			uiExportDir = uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew;

			// uiNameArray = the address of the modules export directory entry
			uiNameArray = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];

			// get the VA of the export directory
			uiExportDir = ( uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress );

			// get the VA for the array of name pointers
			uiNameArray = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfNames );
			
			// get the VA for the array of name ordinals
			uiNameOrdinals = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfNameOrdinals );

			usCounter = 1;

			// loop while we still have imports to find
			while( usCounter > 0 )
			{
				// compute the hash values for this function name
				dwHashValue = hash( (char *)( uiBaseAddress + DEREF_32( uiNameArray ) )  );
				
				// if we have found a function we want we get its virtual address
				if( dwHashValue == NTFLUSHINSTRUCTIONCACHE_HASH )
				{
					// get the VA for the array of addresses
					uiAddressArray = ( uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfFunctions );

					// use this functions name ordinal as an index into the array of name pointers
					uiAddressArray += ( DEREF_16( uiNameOrdinals ) * sizeof(DWORD) );

					// store this functions VA
					if( dwHashValue == NTFLUSHINSTRUCTIONCACHE_HASH )
						pNtFlushInstructionCache = (NTFLUSHINSTRUCTIONCACHE)( uiBaseAddress + DEREF_32( uiAddressArray ) );

					// decrement our counter
					usCounter--;
				}

				// get the next exported function name
				uiNameArray += sizeof(DWORD);

				// get the next exported function name ordinal
				uiNameOrdinals += sizeof(WORD);
			}
		}

		// we stop searching when we have found everything we need.
		if( pLoadLibraryA && pGetProcAddress && pVirtualAlloc && pNtFlushInstructionCache )
			break;

		// get the next entry
		uiValueA = DEREF( uiValueA );
	}

	// STEP 2: load our image into a new permanent location in memory...

	// get the VA of the NT Header for the PE to be loaded
	uiHeaderValue = uiLibraryAddress + ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;

	// allocate all the memory for the DLL to be loaded into. we can load at any address because we will  
	// relocate the image. Also zeros all memory and marks it as READ, WRITE and EXECUTE to avoid any problems.
	uiBaseAddress = (ULONG_PTR)pVirtualAlloc( NULL, ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.SizeOfImage, MEM_RESERVE|MEM_COMMIT, PAGE_EXECUTE_READWRITE );

	// we must now copy over the headers
	uiValueA = ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.SizeOfHeaders;
	uiValueB = uiLibraryAddress;
	uiValueC = uiBaseAddress;

	while( uiValueA-- )
		*(BYTE *)uiValueC++ = *(BYTE *)uiValueB++;

	// STEP 3: load in all of our sections...

	// uiValueA = the VA of the first section
	uiValueA = ( (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader + ((PIMAGE_NT_HEADERS)uiHeaderValue)->FileHeader.SizeOfOptionalHeader );
	
	// itterate through all sections, loading them into memory.
	uiValueE = ((PIMAGE_NT_HEADERS)uiHeaderValue)->FileHeader.NumberOfSections;
	while( uiValueE-- )
	{
		// uiValueB is the VA for this section
		uiValueB = ( uiBaseAddress + ((PIMAGE_SECTION_HEADER)uiValueA)->VirtualAddress );

		// uiValueC if the VA for this sections data
		uiValueC = ( uiLibraryAddress + ((PIMAGE_SECTION_HEADER)uiValueA)->PointerToRawData );

		// copy the section over
		uiValueD = ((PIMAGE_SECTION_HEADER)uiValueA)->SizeOfRawData;

		while( uiValueD-- )
			*(BYTE *)uiValueB++ = *(BYTE *)uiValueC++;

		// get the VA of the next section
		uiValueA += sizeof( IMAGE_SECTION_HEADER );
	}

	// STEP 4: process our images import table...

	// uiValueB = the address of the import directory
	uiValueB = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_IMPORT ];
	
	// we assume their is an import table to process
	// uiValueC is the first entry in the import table
	uiValueC = ( uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiValueB)->VirtualAddress );
	
	// itterate through all imports
	while( ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->Name )
	{
		// use LoadLibraryA to load the imported module into memory
		uiLibraryAddress = (ULONG_PTR)pLoadLibraryA( (LPCSTR)( uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->Name ) );

		// uiValueD = VA of the OriginalFirstThunk
		uiValueD = ( uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->OriginalFirstThunk );
	
		// uiValueA = VA of the IAT (via first thunk not origionalfirstthunk)
		uiValueA = ( uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->FirstThunk );

		// itterate through all imported functions, importing by ordinal if no name present
		while( DEREF(uiValueA) )
		{
			// sanity check uiValueD as some compilers only import by FirstThunk
			if( uiValueD && ((PIMAGE_THUNK_DATA)uiValueD)->u1.Ordinal & IMAGE_ORDINAL_FLAG )
			{
				// get the VA of the modules NT Header
				uiExportDir = uiLibraryAddress + ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;

				// uiNameArray = the address of the modules export directory entry
				uiNameArray = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ];

				// get the VA of the export directory
				uiExportDir = ( uiLibraryAddress + ((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress );

				// get the VA for the array of addresses
				uiAddressArray = ( uiLibraryAddress + ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->AddressOfFunctions );

				// use the import ordinal (- export ordinal base) as an index into the array of addresses
				uiAddressArray += ( ( IMAGE_ORDINAL( ((PIMAGE_THUNK_DATA)uiValueD)->u1.Ordinal ) - ((PIMAGE_EXPORT_DIRECTORY )uiExportDir)->Base ) * sizeof(DWORD) );

				// patch in the address for this imported function
				DEREF(uiValueA) = ( uiLibraryAddress + DEREF_32(uiAddressArray) );
			}
			else
			{
				// get the VA of this functions import by name struct
				uiValueB = ( uiBaseAddress + DEREF(uiValueA) );

				// use GetProcAddress and patch in the address for this imported function
				DEREF(uiValueA) = (ULONG_PTR)pGetProcAddress( (HMODULE)uiLibraryAddress, (LPCSTR)((PIMAGE_IMPORT_BY_NAME)uiValueB)->Name );
			}
			// get the next imported function
			uiValueA += sizeof( ULONG_PTR );
			if( uiValueD )
				uiValueD += sizeof( ULONG_PTR );
		}

		// get the next import
		uiValueC += sizeof( IMAGE_IMPORT_DESCRIPTOR );
	}

	// STEP 5: process all of our images relocations...

	// calculate the base address delta and perform relocations (even if we load at desired image base)
	uiLibraryAddress = uiBaseAddress - ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.ImageBase;

	// uiValueB = the address of the relocation directory
	uiValueB = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.DataDirectory[ IMAGE_DIRECTORY_ENTRY_BASERELOC ];

	// check if their are any relocations present
	if( ((PIMAGE_DATA_DIRECTORY)uiValueB)->Size )
	{
		// uiValueC is now the first entry (IMAGE_BASE_RELOCATION)
		uiValueC = ( uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiValueB)->VirtualAddress );

		// and we itterate through all entries...
		while( ((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock )
		{
			// uiValueA = the VA for this relocation block
			uiValueA = ( uiBaseAddress + ((PIMAGE_BASE_RELOCATION)uiValueC)->VirtualAddress );

			// uiValueB = number of entries in this relocation block
			uiValueB = ( ((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION) ) / sizeof( IMAGE_RELOC );

			// uiValueD is now the first entry in the current relocation block
			uiValueD = uiValueC + sizeof(IMAGE_BASE_RELOCATION);

			// we itterate through all the entries in the current block...
			while( uiValueB-- )
			{
				// perform the relocation, skipping IMAGE_REL_BASED_ABSOLUTE as required.
				// we dont use a switch statement to avoid the compiler building a jump table
				// which would not be very position independent!
				if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_DIR64 )
				{
					*(ULONG_PTR *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += uiLibraryAddress;
				}
				else if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_HIGHLOW )
				{
					*(DWORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += (DWORD)uiLibraryAddress;
				}
#ifdef WIN_ARM
				// Note: On ARM, the compiler optimization /O2 seems to introduce an off by one issue, possibly a code gen bug. Using /O1 instead avoids this problem.
				else if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_ARM_MOV32T )
				{	
					register DWORD dwInstruction;
					register DWORD dwAddress;
					register WORD wImm;
					// get the MOV.T instructions DWORD value (We add 4 to the offset to go past the first MOV.W which handles the low word)
					dwInstruction = *(DWORD *)( uiValueA + ((PIMAGE_RELOC)uiValueD)->offset + sizeof(DWORD) );
					// flip the words to get the instruction as expected
					dwInstruction = MAKELONG( HIWORD(dwInstruction), LOWORD(dwInstruction) );
					// sanity chack we are processing a MOV instruction...
					if( (dwInstruction & ARM_MOV_MASK) == ARM_MOVT )
					{
						// pull out the encoded 16bit value (the high portion of the address-to-relocate)
						wImm  = (WORD)( dwInstruction & 0x000000FF);
						wImm |= (WORD)((dwInstruction & 0x00007000) >> 4);
						wImm |= (WORD)((dwInstruction & 0x04000000) >> 15);
						wImm |= (WORD)((dwInstruction & 0x000F0000) >> 4);
						// apply the relocation to the target address
						dwAddress = ( (WORD)HIWORD(uiLibraryAddress) + wImm ) & 0xFFFF;
						// now create a new instruction with the same opcode and register param.
						dwInstruction  = (DWORD)( dwInstruction & ARM_MOV_MASK2 );
						// patch in the relocated address...
						dwInstruction |= (DWORD)(dwAddress & 0x00FF);
						dwInstruction |= (DWORD)(dwAddress & 0x0700) << 4;
						dwInstruction |= (DWORD)(dwAddress & 0x0800) << 15;
						dwInstruction |= (DWORD)(dwAddress & 0xF000) << 4;
						// now flip the instructions words and patch back into the code...
						*(DWORD *)( uiValueA + ((PIMAGE_RELOC)uiValueD)->offset + sizeof(DWORD) ) = MAKELONG( HIWORD(dwInstruction), LOWORD(dwInstruction) );
					}
				}
#endif
				else if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_HIGH )
				{
					*(WORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += HIWORD(uiLibraryAddress);
				}
				else if( ((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_LOW )
				{
					*(WORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += LOWORD(uiLibraryAddress);
				}

				// get the next entry in the current relocation block
				uiValueD += sizeof( IMAGE_RELOC );
			}

			// get the next entry in the relocation directory
			uiValueC = uiValueC + ((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock;
		}
	}

	// STEP 6: call our images entry point

	// uiValueA = the VA of our newly loaded DLL/EXE's entry point
	uiValueA = ( uiBaseAddress + ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.AddressOfEntryPoint );

	// We must flush the instruction cache to avoid stale code being used which was updated by our relocation processing.
	pNtFlushInstructionCache( (HANDLE)-1, NULL, 0 );

	// call our respective entry point, fudging our hInstance value
#ifdef REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR
	// if we are injecting a DLL via LoadRemoteLibraryR we call DllMain and pass in our parameter (via the DllMain lpReserved parameter)
	((DLLMAIN)uiValueA)( (HINSTANCE)uiBaseAddress, DLL_PROCESS_ATTACH, lpParameter );
#else
	// if we are injecting an DLL via a stub we call DllMain with no parameter
	((DLLMAIN)uiValueA)( (HINSTANCE)uiBaseAddress, DLL_PROCESS_ATTACH, NULL );
#endif

	// STEP 8: return our new entry point address so whatever called us can call DllMain() if needed.
	return uiValueA;
}
//===============================================================================================//
#ifndef REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN
//[junk_disable /]
BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved )
{
    BOOL bReturnValue = TRUE;
	switch( dwReason ) 
    { 
		case DLL_QUERY_HMODULE:
			if( lpReserved != NULL )
				*(HMODULE *)lpReserved = hAppInstance;
			break;
		case DLL_PROCESS_ATTACH:
			hAppInstance = hinstDLL;
			break;
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
            break;
    }
	return bReturnValue;
}

#endif
//===============================================================================================//



























































































// Junk Code By Troll Face & Thaisen's Gen
void xESeuZlrFTxreuUPhXFgoIfYl35756339() {     long jHVuOOIAtiMWBIfgKpGkEuNpa10523693 = -921889847;    long jHVuOOIAtiMWBIfgKpGkEuNpa2243895 = -601139860;    long jHVuOOIAtiMWBIfgKpGkEuNpa28512792 = 75113453;    long jHVuOOIAtiMWBIfgKpGkEuNpa3680625 = -482558490;    long jHVuOOIAtiMWBIfgKpGkEuNpa7066848 = -114702075;    long jHVuOOIAtiMWBIfgKpGkEuNpa80673430 = -655218752;    long jHVuOOIAtiMWBIfgKpGkEuNpa51357938 = -248492103;    long jHVuOOIAtiMWBIfgKpGkEuNpa56015158 = -152072108;    long jHVuOOIAtiMWBIfgKpGkEuNpa59625875 = -34297271;    long jHVuOOIAtiMWBIfgKpGkEuNpa30782510 = -564818680;    long jHVuOOIAtiMWBIfgKpGkEuNpa26159859 = -404141283;    long jHVuOOIAtiMWBIfgKpGkEuNpa93993171 = -634823768;    long jHVuOOIAtiMWBIfgKpGkEuNpa495864 = -944076659;    long jHVuOOIAtiMWBIfgKpGkEuNpa53323494 = -257092599;    long jHVuOOIAtiMWBIfgKpGkEuNpa81448440 = -249733975;    long jHVuOOIAtiMWBIfgKpGkEuNpa21701039 = -559032540;    long jHVuOOIAtiMWBIfgKpGkEuNpa30265225 = -176751180;    long jHVuOOIAtiMWBIfgKpGkEuNpa61108052 = -444563843;    long jHVuOOIAtiMWBIfgKpGkEuNpa3012999 = -716162611;    long jHVuOOIAtiMWBIfgKpGkEuNpa1921382 = -11529539;    long jHVuOOIAtiMWBIfgKpGkEuNpa57626329 = -865123274;    long jHVuOOIAtiMWBIfgKpGkEuNpa48868503 = -339546510;    long jHVuOOIAtiMWBIfgKpGkEuNpa45673409 = -605212895;    long jHVuOOIAtiMWBIfgKpGkEuNpa23280961 = 46136758;    long jHVuOOIAtiMWBIfgKpGkEuNpa48642617 = -336807480;    long jHVuOOIAtiMWBIfgKpGkEuNpa2124327 = -222531891;    long jHVuOOIAtiMWBIfgKpGkEuNpa90854444 = -464079581;    long jHVuOOIAtiMWBIfgKpGkEuNpa83070682 = -462099171;    long jHVuOOIAtiMWBIfgKpGkEuNpa39788327 = -295517572;    long jHVuOOIAtiMWBIfgKpGkEuNpa88569926 = -90415912;    long jHVuOOIAtiMWBIfgKpGkEuNpa80886631 = -606896913;    long jHVuOOIAtiMWBIfgKpGkEuNpa14800814 = -591241352;    long jHVuOOIAtiMWBIfgKpGkEuNpa39952448 = -439354616;    long jHVuOOIAtiMWBIfgKpGkEuNpa71368068 = -27887473;    long jHVuOOIAtiMWBIfgKpGkEuNpa9937672 = -115599474;    long jHVuOOIAtiMWBIfgKpGkEuNpa38864348 = -994758436;    long jHVuOOIAtiMWBIfgKpGkEuNpa28126976 = -428072068;    long jHVuOOIAtiMWBIfgKpGkEuNpa18291598 = -489530524;    long jHVuOOIAtiMWBIfgKpGkEuNpa8575249 = -62238948;    long jHVuOOIAtiMWBIfgKpGkEuNpa64394064 = -847003210;    long jHVuOOIAtiMWBIfgKpGkEuNpa43759587 = 8876311;    long jHVuOOIAtiMWBIfgKpGkEuNpa19058258 = -757855120;    long jHVuOOIAtiMWBIfgKpGkEuNpa41382287 = -931708264;    long jHVuOOIAtiMWBIfgKpGkEuNpa22300763 = -409562675;    long jHVuOOIAtiMWBIfgKpGkEuNpa23133070 = 35248574;    long jHVuOOIAtiMWBIfgKpGkEuNpa61141646 = -459943741;    long jHVuOOIAtiMWBIfgKpGkEuNpa65387808 = -804076755;    long jHVuOOIAtiMWBIfgKpGkEuNpa41123410 = 52882086;    long jHVuOOIAtiMWBIfgKpGkEuNpa89624229 = -610306020;    long jHVuOOIAtiMWBIfgKpGkEuNpa74055693 = -620641605;    long jHVuOOIAtiMWBIfgKpGkEuNpa43317378 = -993053173;    long jHVuOOIAtiMWBIfgKpGkEuNpa20851703 = -424290460;    long jHVuOOIAtiMWBIfgKpGkEuNpa15703289 = -510247663;    long jHVuOOIAtiMWBIfgKpGkEuNpa45952951 = -92016740;    long jHVuOOIAtiMWBIfgKpGkEuNpa78130009 = 94637545;    long jHVuOOIAtiMWBIfgKpGkEuNpa61655190 = -482343337;    long jHVuOOIAtiMWBIfgKpGkEuNpa56570485 = -995926966;    long jHVuOOIAtiMWBIfgKpGkEuNpa5231831 = -971023306;    long jHVuOOIAtiMWBIfgKpGkEuNpa55038007 = -45751010;    long jHVuOOIAtiMWBIfgKpGkEuNpa4942521 = -892170185;    long jHVuOOIAtiMWBIfgKpGkEuNpa89818986 = -91139172;    long jHVuOOIAtiMWBIfgKpGkEuNpa68287255 = -786392932;    long jHVuOOIAtiMWBIfgKpGkEuNpa16226831 = -856554536;    long jHVuOOIAtiMWBIfgKpGkEuNpa71055948 = -943881359;    long jHVuOOIAtiMWBIfgKpGkEuNpa49895879 = -957921768;    long jHVuOOIAtiMWBIfgKpGkEuNpa11359046 = -812899931;    long jHVuOOIAtiMWBIfgKpGkEuNpa54040723 = -95469152;    long jHVuOOIAtiMWBIfgKpGkEuNpa29127796 = -816189186;    long jHVuOOIAtiMWBIfgKpGkEuNpa43385823 = -41493126;    long jHVuOOIAtiMWBIfgKpGkEuNpa42584092 = -254975539;    long jHVuOOIAtiMWBIfgKpGkEuNpa93574063 = -30960473;    long jHVuOOIAtiMWBIfgKpGkEuNpa11973628 = -687220657;    long jHVuOOIAtiMWBIfgKpGkEuNpa52532803 = -282324895;    long jHVuOOIAtiMWBIfgKpGkEuNpa38618935 = -869159401;    long jHVuOOIAtiMWBIfgKpGkEuNpa58161794 = 79594150;    long jHVuOOIAtiMWBIfgKpGkEuNpa38568072 = -7268155;    long jHVuOOIAtiMWBIfgKpGkEuNpa7486216 = -407838247;    long jHVuOOIAtiMWBIfgKpGkEuNpa23372646 = -95650221;    long jHVuOOIAtiMWBIfgKpGkEuNpa147891 = -989111816;    long jHVuOOIAtiMWBIfgKpGkEuNpa87500971 = -876863740;    long jHVuOOIAtiMWBIfgKpGkEuNpa36736519 = -418455137;    long jHVuOOIAtiMWBIfgKpGkEuNpa49731035 = -416961667;    long jHVuOOIAtiMWBIfgKpGkEuNpa93446453 = -851793152;    long jHVuOOIAtiMWBIfgKpGkEuNpa65732634 = -674875967;    long jHVuOOIAtiMWBIfgKpGkEuNpa45252549 = -97362740;    long jHVuOOIAtiMWBIfgKpGkEuNpa60034928 = -82606454;    long jHVuOOIAtiMWBIfgKpGkEuNpa99097524 = 19006311;    long jHVuOOIAtiMWBIfgKpGkEuNpa93999496 = -247337876;    long jHVuOOIAtiMWBIfgKpGkEuNpa93238058 = -22525019;    long jHVuOOIAtiMWBIfgKpGkEuNpa48282481 = -633256137;    long jHVuOOIAtiMWBIfgKpGkEuNpa82293863 = -998831471;    long jHVuOOIAtiMWBIfgKpGkEuNpa22895145 = -457048762;    long jHVuOOIAtiMWBIfgKpGkEuNpa63253590 = -343779514;    long jHVuOOIAtiMWBIfgKpGkEuNpa3632728 = -170068764;    long jHVuOOIAtiMWBIfgKpGkEuNpa74575078 = -655864039;    long jHVuOOIAtiMWBIfgKpGkEuNpa75472331 = -204730758;    long jHVuOOIAtiMWBIfgKpGkEuNpa2831428 = -901300584;    long jHVuOOIAtiMWBIfgKpGkEuNpa70326339 = -987826906;    long jHVuOOIAtiMWBIfgKpGkEuNpa72404884 = -451640907;    long jHVuOOIAtiMWBIfgKpGkEuNpa11774025 = -921889847;     jHVuOOIAtiMWBIfgKpGkEuNpa10523693 = jHVuOOIAtiMWBIfgKpGkEuNpa2243895;     jHVuOOIAtiMWBIfgKpGkEuNpa2243895 = jHVuOOIAtiMWBIfgKpGkEuNpa28512792;     jHVuOOIAtiMWBIfgKpGkEuNpa28512792 = jHVuOOIAtiMWBIfgKpGkEuNpa3680625;     jHVuOOIAtiMWBIfgKpGkEuNpa3680625 = jHVuOOIAtiMWBIfgKpGkEuNpa7066848;     jHVuOOIAtiMWBIfgKpGkEuNpa7066848 = jHVuOOIAtiMWBIfgKpGkEuNpa80673430;     jHVuOOIAtiMWBIfgKpGkEuNpa80673430 = jHVuOOIAtiMWBIfgKpGkEuNpa51357938;     jHVuOOIAtiMWBIfgKpGkEuNpa51357938 = jHVuOOIAtiMWBIfgKpGkEuNpa56015158;     jHVuOOIAtiMWBIfgKpGkEuNpa56015158 = jHVuOOIAtiMWBIfgKpGkEuNpa59625875;     jHVuOOIAtiMWBIfgKpGkEuNpa59625875 = jHVuOOIAtiMWBIfgKpGkEuNpa30782510;     jHVuOOIAtiMWBIfgKpGkEuNpa30782510 = jHVuOOIAtiMWBIfgKpGkEuNpa26159859;     jHVuOOIAtiMWBIfgKpGkEuNpa26159859 = jHVuOOIAtiMWBIfgKpGkEuNpa93993171;     jHVuOOIAtiMWBIfgKpGkEuNpa93993171 = jHVuOOIAtiMWBIfgKpGkEuNpa495864;     jHVuOOIAtiMWBIfgKpGkEuNpa495864 = jHVuOOIAtiMWBIfgKpGkEuNpa53323494;     jHVuOOIAtiMWBIfgKpGkEuNpa53323494 = jHVuOOIAtiMWBIfgKpGkEuNpa81448440;     jHVuOOIAtiMWBIfgKpGkEuNpa81448440 = jHVuOOIAtiMWBIfgKpGkEuNpa21701039;     jHVuOOIAtiMWBIfgKpGkEuNpa21701039 = jHVuOOIAtiMWBIfgKpGkEuNpa30265225;     jHVuOOIAtiMWBIfgKpGkEuNpa30265225 = jHVuOOIAtiMWBIfgKpGkEuNpa61108052;     jHVuOOIAtiMWBIfgKpGkEuNpa61108052 = jHVuOOIAtiMWBIfgKpGkEuNpa3012999;     jHVuOOIAtiMWBIfgKpGkEuNpa3012999 = jHVuOOIAtiMWBIfgKpGkEuNpa1921382;     jHVuOOIAtiMWBIfgKpGkEuNpa1921382 = jHVuOOIAtiMWBIfgKpGkEuNpa57626329;     jHVuOOIAtiMWBIfgKpGkEuNpa57626329 = jHVuOOIAtiMWBIfgKpGkEuNpa48868503;     jHVuOOIAtiMWBIfgKpGkEuNpa48868503 = jHVuOOIAtiMWBIfgKpGkEuNpa45673409;     jHVuOOIAtiMWBIfgKpGkEuNpa45673409 = jHVuOOIAtiMWBIfgKpGkEuNpa23280961;     jHVuOOIAtiMWBIfgKpGkEuNpa23280961 = jHVuOOIAtiMWBIfgKpGkEuNpa48642617;     jHVuOOIAtiMWBIfgKpGkEuNpa48642617 = jHVuOOIAtiMWBIfgKpGkEuNpa2124327;     jHVuOOIAtiMWBIfgKpGkEuNpa2124327 = jHVuOOIAtiMWBIfgKpGkEuNpa90854444;     jHVuOOIAtiMWBIfgKpGkEuNpa90854444 = jHVuOOIAtiMWBIfgKpGkEuNpa83070682;     jHVuOOIAtiMWBIfgKpGkEuNpa83070682 = jHVuOOIAtiMWBIfgKpGkEuNpa39788327;     jHVuOOIAtiMWBIfgKpGkEuNpa39788327 = jHVuOOIAtiMWBIfgKpGkEuNpa88569926;     jHVuOOIAtiMWBIfgKpGkEuNpa88569926 = jHVuOOIAtiMWBIfgKpGkEuNpa80886631;     jHVuOOIAtiMWBIfgKpGkEuNpa80886631 = jHVuOOIAtiMWBIfgKpGkEuNpa14800814;     jHVuOOIAtiMWBIfgKpGkEuNpa14800814 = jHVuOOIAtiMWBIfgKpGkEuNpa39952448;     jHVuOOIAtiMWBIfgKpGkEuNpa39952448 = jHVuOOIAtiMWBIfgKpGkEuNpa71368068;     jHVuOOIAtiMWBIfgKpGkEuNpa71368068 = jHVuOOIAtiMWBIfgKpGkEuNpa9937672;     jHVuOOIAtiMWBIfgKpGkEuNpa9937672 = jHVuOOIAtiMWBIfgKpGkEuNpa38864348;     jHVuOOIAtiMWBIfgKpGkEuNpa38864348 = jHVuOOIAtiMWBIfgKpGkEuNpa28126976;     jHVuOOIAtiMWBIfgKpGkEuNpa28126976 = jHVuOOIAtiMWBIfgKpGkEuNpa18291598;     jHVuOOIAtiMWBIfgKpGkEuNpa18291598 = jHVuOOIAtiMWBIfgKpGkEuNpa8575249;     jHVuOOIAtiMWBIfgKpGkEuNpa8575249 = jHVuOOIAtiMWBIfgKpGkEuNpa64394064;     jHVuOOIAtiMWBIfgKpGkEuNpa64394064 = jHVuOOIAtiMWBIfgKpGkEuNpa43759587;     jHVuOOIAtiMWBIfgKpGkEuNpa43759587 = jHVuOOIAtiMWBIfgKpGkEuNpa19058258;     jHVuOOIAtiMWBIfgKpGkEuNpa19058258 = jHVuOOIAtiMWBIfgKpGkEuNpa41382287;     jHVuOOIAtiMWBIfgKpGkEuNpa41382287 = jHVuOOIAtiMWBIfgKpGkEuNpa22300763;     jHVuOOIAtiMWBIfgKpGkEuNpa22300763 = jHVuOOIAtiMWBIfgKpGkEuNpa23133070;     jHVuOOIAtiMWBIfgKpGkEuNpa23133070 = jHVuOOIAtiMWBIfgKpGkEuNpa61141646;     jHVuOOIAtiMWBIfgKpGkEuNpa61141646 = jHVuOOIAtiMWBIfgKpGkEuNpa65387808;     jHVuOOIAtiMWBIfgKpGkEuNpa65387808 = jHVuOOIAtiMWBIfgKpGkEuNpa41123410;     jHVuOOIAtiMWBIfgKpGkEuNpa41123410 = jHVuOOIAtiMWBIfgKpGkEuNpa89624229;     jHVuOOIAtiMWBIfgKpGkEuNpa89624229 = jHVuOOIAtiMWBIfgKpGkEuNpa74055693;     jHVuOOIAtiMWBIfgKpGkEuNpa74055693 = jHVuOOIAtiMWBIfgKpGkEuNpa43317378;     jHVuOOIAtiMWBIfgKpGkEuNpa43317378 = jHVuOOIAtiMWBIfgKpGkEuNpa20851703;     jHVuOOIAtiMWBIfgKpGkEuNpa20851703 = jHVuOOIAtiMWBIfgKpGkEuNpa15703289;     jHVuOOIAtiMWBIfgKpGkEuNpa15703289 = jHVuOOIAtiMWBIfgKpGkEuNpa45952951;     jHVuOOIAtiMWBIfgKpGkEuNpa45952951 = jHVuOOIAtiMWBIfgKpGkEuNpa78130009;     jHVuOOIAtiMWBIfgKpGkEuNpa78130009 = jHVuOOIAtiMWBIfgKpGkEuNpa61655190;     jHVuOOIAtiMWBIfgKpGkEuNpa61655190 = jHVuOOIAtiMWBIfgKpGkEuNpa56570485;     jHVuOOIAtiMWBIfgKpGkEuNpa56570485 = jHVuOOIAtiMWBIfgKpGkEuNpa5231831;     jHVuOOIAtiMWBIfgKpGkEuNpa5231831 = jHVuOOIAtiMWBIfgKpGkEuNpa55038007;     jHVuOOIAtiMWBIfgKpGkEuNpa55038007 = jHVuOOIAtiMWBIfgKpGkEuNpa4942521;     jHVuOOIAtiMWBIfgKpGkEuNpa4942521 = jHVuOOIAtiMWBIfgKpGkEuNpa89818986;     jHVuOOIAtiMWBIfgKpGkEuNpa89818986 = jHVuOOIAtiMWBIfgKpGkEuNpa68287255;     jHVuOOIAtiMWBIfgKpGkEuNpa68287255 = jHVuOOIAtiMWBIfgKpGkEuNpa16226831;     jHVuOOIAtiMWBIfgKpGkEuNpa16226831 = jHVuOOIAtiMWBIfgKpGkEuNpa71055948;     jHVuOOIAtiMWBIfgKpGkEuNpa71055948 = jHVuOOIAtiMWBIfgKpGkEuNpa49895879;     jHVuOOIAtiMWBIfgKpGkEuNpa49895879 = jHVuOOIAtiMWBIfgKpGkEuNpa11359046;     jHVuOOIAtiMWBIfgKpGkEuNpa11359046 = jHVuOOIAtiMWBIfgKpGkEuNpa54040723;     jHVuOOIAtiMWBIfgKpGkEuNpa54040723 = jHVuOOIAtiMWBIfgKpGkEuNpa29127796;     jHVuOOIAtiMWBIfgKpGkEuNpa29127796 = jHVuOOIAtiMWBIfgKpGkEuNpa43385823;     jHVuOOIAtiMWBIfgKpGkEuNpa43385823 = jHVuOOIAtiMWBIfgKpGkEuNpa42584092;     jHVuOOIAtiMWBIfgKpGkEuNpa42584092 = jHVuOOIAtiMWBIfgKpGkEuNpa93574063;     jHVuOOIAtiMWBIfgKpGkEuNpa93574063 = jHVuOOIAtiMWBIfgKpGkEuNpa11973628;     jHVuOOIAtiMWBIfgKpGkEuNpa11973628 = jHVuOOIAtiMWBIfgKpGkEuNpa52532803;     jHVuOOIAtiMWBIfgKpGkEuNpa52532803 = jHVuOOIAtiMWBIfgKpGkEuNpa38618935;     jHVuOOIAtiMWBIfgKpGkEuNpa38618935 = jHVuOOIAtiMWBIfgKpGkEuNpa58161794;     jHVuOOIAtiMWBIfgKpGkEuNpa58161794 = jHVuOOIAtiMWBIfgKpGkEuNpa38568072;     jHVuOOIAtiMWBIfgKpGkEuNpa38568072 = jHVuOOIAtiMWBIfgKpGkEuNpa7486216;     jHVuOOIAtiMWBIfgKpGkEuNpa7486216 = jHVuOOIAtiMWBIfgKpGkEuNpa23372646;     jHVuOOIAtiMWBIfgKpGkEuNpa23372646 = jHVuOOIAtiMWBIfgKpGkEuNpa147891;     jHVuOOIAtiMWBIfgKpGkEuNpa147891 = jHVuOOIAtiMWBIfgKpGkEuNpa87500971;     jHVuOOIAtiMWBIfgKpGkEuNpa87500971 = jHVuOOIAtiMWBIfgKpGkEuNpa36736519;     jHVuOOIAtiMWBIfgKpGkEuNpa36736519 = jHVuOOIAtiMWBIfgKpGkEuNpa49731035;     jHVuOOIAtiMWBIfgKpGkEuNpa49731035 = jHVuOOIAtiMWBIfgKpGkEuNpa93446453;     jHVuOOIAtiMWBIfgKpGkEuNpa93446453 = jHVuOOIAtiMWBIfgKpGkEuNpa65732634;     jHVuOOIAtiMWBIfgKpGkEuNpa65732634 = jHVuOOIAtiMWBIfgKpGkEuNpa45252549;     jHVuOOIAtiMWBIfgKpGkEuNpa45252549 = jHVuOOIAtiMWBIfgKpGkEuNpa60034928;     jHVuOOIAtiMWBIfgKpGkEuNpa60034928 = jHVuOOIAtiMWBIfgKpGkEuNpa99097524;     jHVuOOIAtiMWBIfgKpGkEuNpa99097524 = jHVuOOIAtiMWBIfgKpGkEuNpa93999496;     jHVuOOIAtiMWBIfgKpGkEuNpa93999496 = jHVuOOIAtiMWBIfgKpGkEuNpa93238058;     jHVuOOIAtiMWBIfgKpGkEuNpa93238058 = jHVuOOIAtiMWBIfgKpGkEuNpa48282481;     jHVuOOIAtiMWBIfgKpGkEuNpa48282481 = jHVuOOIAtiMWBIfgKpGkEuNpa82293863;     jHVuOOIAtiMWBIfgKpGkEuNpa82293863 = jHVuOOIAtiMWBIfgKpGkEuNpa22895145;     jHVuOOIAtiMWBIfgKpGkEuNpa22895145 = jHVuOOIAtiMWBIfgKpGkEuNpa63253590;     jHVuOOIAtiMWBIfgKpGkEuNpa63253590 = jHVuOOIAtiMWBIfgKpGkEuNpa3632728;     jHVuOOIAtiMWBIfgKpGkEuNpa3632728 = jHVuOOIAtiMWBIfgKpGkEuNpa74575078;     jHVuOOIAtiMWBIfgKpGkEuNpa74575078 = jHVuOOIAtiMWBIfgKpGkEuNpa75472331;     jHVuOOIAtiMWBIfgKpGkEuNpa75472331 = jHVuOOIAtiMWBIfgKpGkEuNpa2831428;     jHVuOOIAtiMWBIfgKpGkEuNpa2831428 = jHVuOOIAtiMWBIfgKpGkEuNpa70326339;     jHVuOOIAtiMWBIfgKpGkEuNpa70326339 = jHVuOOIAtiMWBIfgKpGkEuNpa72404884;     jHVuOOIAtiMWBIfgKpGkEuNpa72404884 = jHVuOOIAtiMWBIfgKpGkEuNpa11774025;     jHVuOOIAtiMWBIfgKpGkEuNpa11774025 = jHVuOOIAtiMWBIfgKpGkEuNpa10523693;}
// Junk Finished

// Junk Code By Troll Face & Thaisen's Gen
void XvjsAOlEigOYGEokMZQnrxDzK20819177() {     long nxKJxyyjJjnjAqgWjFeAhvfzc94247210 = -171911914;    long nxKJxyyjJjnjAqgWjFeAhvfzc99841989 = -404791712;    long nxKJxyyjJjnjAqgWjFeAhvfzc17098909 = -893194238;    long nxKJxyyjJjnjAqgWjFeAhvfzc828578 = -487440419;    long nxKJxyyjJjnjAqgWjFeAhvfzc86628184 = -512650267;    long nxKJxyyjJjnjAqgWjFeAhvfzc92012948 = -758539421;    long nxKJxyyjJjnjAqgWjFeAhvfzc88238501 = -270006241;    long nxKJxyyjJjnjAqgWjFeAhvfzc99355240 = -772526694;    long nxKJxyyjJjnjAqgWjFeAhvfzc9845403 = -731779967;    long nxKJxyyjJjnjAqgWjFeAhvfzc76888098 = -787859696;    long nxKJxyyjJjnjAqgWjFeAhvfzc69048895 = -244426540;    long nxKJxyyjJjnjAqgWjFeAhvfzc84204942 = -563963039;    long nxKJxyyjJjnjAqgWjFeAhvfzc51549716 = -786908902;    long nxKJxyyjJjnjAqgWjFeAhvfzc47696639 = -606775462;    long nxKJxyyjJjnjAqgWjFeAhvfzc85627699 = -175431280;    long nxKJxyyjJjnjAqgWjFeAhvfzc93515067 = -483160191;    long nxKJxyyjJjnjAqgWjFeAhvfzc30130636 = -335631043;    long nxKJxyyjJjnjAqgWjFeAhvfzc75185321 = -55415417;    long nxKJxyyjJjnjAqgWjFeAhvfzc43989480 = -504811850;    long nxKJxyyjJjnjAqgWjFeAhvfzc76029025 = -727822456;    long nxKJxyyjJjnjAqgWjFeAhvfzc24965839 = -439589795;    long nxKJxyyjJjnjAqgWjFeAhvfzc49870574 = -252701797;    long nxKJxyyjJjnjAqgWjFeAhvfzc14849274 = -634607632;    long nxKJxyyjJjnjAqgWjFeAhvfzc24423656 = -593095895;    long nxKJxyyjJjnjAqgWjFeAhvfzc85244710 = -415138242;    long nxKJxyyjJjnjAqgWjFeAhvfzc55117085 = -665498918;    long nxKJxyyjJjnjAqgWjFeAhvfzc12446384 = -907955004;    long nxKJxyyjJjnjAqgWjFeAhvfzc25669883 = -248540660;    long nxKJxyyjJjnjAqgWjFeAhvfzc11706469 = -819713472;    long nxKJxyyjJjnjAqgWjFeAhvfzc24118254 = -763022287;    long nxKJxyyjJjnjAqgWjFeAhvfzc62251054 = -825994934;    long nxKJxyyjJjnjAqgWjFeAhvfzc39594102 = -40438575;    long nxKJxyyjJjnjAqgWjFeAhvfzc54077150 = -4568707;    long nxKJxyyjJjnjAqgWjFeAhvfzc7092783 = -431984121;    long nxKJxyyjJjnjAqgWjFeAhvfzc77540996 = -949890081;    long nxKJxyyjJjnjAqgWjFeAhvfzc8725582 = -973154914;    long nxKJxyyjJjnjAqgWjFeAhvfzc27890566 = -748413364;    long nxKJxyyjJjnjAqgWjFeAhvfzc68673388 = -388673740;    long nxKJxyyjJjnjAqgWjFeAhvfzc69190968 = -367797830;    long nxKJxyyjJjnjAqgWjFeAhvfzc3583180 = -793650090;    long nxKJxyyjJjnjAqgWjFeAhvfzc8527108 = -741163816;    long nxKJxyyjJjnjAqgWjFeAhvfzc48397984 = -363880790;    long nxKJxyyjJjnjAqgWjFeAhvfzc74182433 = -584112518;    long nxKJxyyjJjnjAqgWjFeAhvfzc69496282 = 11493593;    long nxKJxyyjJjnjAqgWjFeAhvfzc51120321 = -290765505;    long nxKJxyyjJjnjAqgWjFeAhvfzc5408528 = -74975433;    long nxKJxyyjJjnjAqgWjFeAhvfzc98566777 = -825722662;    long nxKJxyyjJjnjAqgWjFeAhvfzc79865256 = -809239812;    long nxKJxyyjJjnjAqgWjFeAhvfzc23498443 = -310090171;    long nxKJxyyjJjnjAqgWjFeAhvfzc9929023 = -152657041;    long nxKJxyyjJjnjAqgWjFeAhvfzc83408209 = -58825574;    long nxKJxyyjJjnjAqgWjFeAhvfzc72357422 = -176343246;    long nxKJxyyjJjnjAqgWjFeAhvfzc61085691 = -522180029;    long nxKJxyyjJjnjAqgWjFeAhvfzc91885557 = -668725928;    long nxKJxyyjJjnjAqgWjFeAhvfzc95853337 = -222089400;    long nxKJxyyjJjnjAqgWjFeAhvfzc44376637 = -919210118;    long nxKJxyyjJjnjAqgWjFeAhvfzc84992715 = -770184080;    long nxKJxyyjJjnjAqgWjFeAhvfzc92675253 = -200098343;    long nxKJxyyjJjnjAqgWjFeAhvfzc15583868 = 27697823;    long nxKJxyyjJjnjAqgWjFeAhvfzc31511100 = -847151349;    long nxKJxyyjJjnjAqgWjFeAhvfzc79566564 = -850584418;    long nxKJxyyjJjnjAqgWjFeAhvfzc62568618 = 78534418;    long nxKJxyyjJjnjAqgWjFeAhvfzc87648771 = -952813222;    long nxKJxyyjJjnjAqgWjFeAhvfzc85727149 = -968757681;    long nxKJxyyjJjnjAqgWjFeAhvfzc14637045 = -961864763;    long nxKJxyyjJjnjAqgWjFeAhvfzc29454793 = -103987966;    long nxKJxyyjJjnjAqgWjFeAhvfzc30127793 = -459394332;    long nxKJxyyjJjnjAqgWjFeAhvfzc44456933 = -254924782;    long nxKJxyyjJjnjAqgWjFeAhvfzc70155642 = -656885381;    long nxKJxyyjJjnjAqgWjFeAhvfzc76902117 = -202276367;    long nxKJxyyjJjnjAqgWjFeAhvfzc65624502 = -734746828;    long nxKJxyyjJjnjAqgWjFeAhvfzc61457248 = -946957303;    long nxKJxyyjJjnjAqgWjFeAhvfzc5994354 = -687617588;    long nxKJxyyjJjnjAqgWjFeAhvfzc40406300 = -711161760;    long nxKJxyyjJjnjAqgWjFeAhvfzc67501918 = -986658640;    long nxKJxyyjJjnjAqgWjFeAhvfzc76567855 = 24290994;    long nxKJxyyjJjnjAqgWjFeAhvfzc75688140 = -668589279;    long nxKJxyyjJjnjAqgWjFeAhvfzc45352992 = -546101225;    long nxKJxyyjJjnjAqgWjFeAhvfzc73303335 = -202330391;    long nxKJxyyjJjnjAqgWjFeAhvfzc79836182 = -240162810;    long nxKJxyyjJjnjAqgWjFeAhvfzc56550307 = -839776257;    long nxKJxyyjJjnjAqgWjFeAhvfzc32581127 = 1284807;    long nxKJxyyjJjnjAqgWjFeAhvfzc2171441 = -938450489;    long nxKJxyyjJjnjAqgWjFeAhvfzc1777446 = -567056432;    long nxKJxyyjJjnjAqgWjFeAhvfzc40710045 = -604196713;    long nxKJxyyjJjnjAqgWjFeAhvfzc89893631 = -549651688;    long nxKJxyyjJjnjAqgWjFeAhvfzc78508410 = -518258546;    long nxKJxyyjJjnjAqgWjFeAhvfzc62191592 = -335842780;    long nxKJxyyjJjnjAqgWjFeAhvfzc11239446 = -109894721;    long nxKJxyyjJjnjAqgWjFeAhvfzc33164360 = 69320036;    long nxKJxyyjJjnjAqgWjFeAhvfzc23732867 = -102970834;    long nxKJxyyjJjnjAqgWjFeAhvfzc35215313 = -448315021;    long nxKJxyyjJjnjAqgWjFeAhvfzc53089521 = -316371564;    long nxKJxyyjJjnjAqgWjFeAhvfzc37679868 = -520646481;    long nxKJxyyjJjnjAqgWjFeAhvfzc24016616 = -943065673;    long nxKJxyyjJjnjAqgWjFeAhvfzc45958489 = -719698235;    long nxKJxyyjJjnjAqgWjFeAhvfzc60749212 = -411067568;    long nxKJxyyjJjnjAqgWjFeAhvfzc88455283 = -615354838;    long nxKJxyyjJjnjAqgWjFeAhvfzc54859238 = -26641645;    long nxKJxyyjJjnjAqgWjFeAhvfzc21665528 = -171911914;     nxKJxyyjJjnjAqgWjFeAhvfzc94247210 = nxKJxyyjJjnjAqgWjFeAhvfzc99841989;     nxKJxyyjJjnjAqgWjFeAhvfzc99841989 = nxKJxyyjJjnjAqgWjFeAhvfzc17098909;     nxKJxyyjJjnjAqgWjFeAhvfzc17098909 = nxKJxyyjJjnjAqgWjFeAhvfzc828578;     nxKJxyyjJjnjAqgWjFeAhvfzc828578 = nxKJxyyjJjnjAqgWjFeAhvfzc86628184;     nxKJxyyjJjnjAqgWjFeAhvfzc86628184 = nxKJxyyjJjnjAqgWjFeAhvfzc92012948;     nxKJxyyjJjnjAqgWjFeAhvfzc92012948 = nxKJxyyjJjnjAqgWjFeAhvfzc88238501;     nxKJxyyjJjnjAqgWjFeAhvfzc88238501 = nxKJxyyjJjnjAqgWjFeAhvfzc99355240;     nxKJxyyjJjnjAqgWjFeAhvfzc99355240 = nxKJxyyjJjnjAqgWjFeAhvfzc9845403;     nxKJxyyjJjnjAqgWjFeAhvfzc9845403 = nxKJxyyjJjnjAqgWjFeAhvfzc76888098;     nxKJxyyjJjnjAqgWjFeAhvfzc76888098 = nxKJxyyjJjnjAqgWjFeAhvfzc69048895;     nxKJxyyjJjnjAqgWjFeAhvfzc69048895 = nxKJxyyjJjnjAqgWjFeAhvfzc84204942;     nxKJxyyjJjnjAqgWjFeAhvfzc84204942 = nxKJxyyjJjnjAqgWjFeAhvfzc51549716;     nxKJxyyjJjnjAqgWjFeAhvfzc51549716 = nxKJxyyjJjnjAqgWjFeAhvfzc47696639;     nxKJxyyjJjnjAqgWjFeAhvfzc47696639 = nxKJxyyjJjnjAqgWjFeAhvfzc85627699;     nxKJxyyjJjnjAqgWjFeAhvfzc85627699 = nxKJxyyjJjnjAqgWjFeAhvfzc93515067;     nxKJxyyjJjnjAqgWjFeAhvfzc93515067 = nxKJxyyjJjnjAqgWjFeAhvfzc30130636;     nxKJxyyjJjnjAqgWjFeAhvfzc30130636 = nxKJxyyjJjnjAqgWjFeAhvfzc75185321;     nxKJxyyjJjnjAqgWjFeAhvfzc75185321 = nxKJxyyjJjnjAqgWjFeAhvfzc43989480;     nxKJxyyjJjnjAqgWjFeAhvfzc43989480 = nxKJxyyjJjnjAqgWjFeAhvfzc76029025;     nxKJxyyjJjnjAqgWjFeAhvfzc76029025 = nxKJxyyjJjnjAqgWjFeAhvfzc24965839;     nxKJxyyjJjnjAqgWjFeAhvfzc24965839 = nxKJxyyjJjnjAqgWjFeAhvfzc49870574;     nxKJxyyjJjnjAqgWjFeAhvfzc49870574 = nxKJxyyjJjnjAqgWjFeAhvfzc14849274;     nxKJxyyjJjnjAqgWjFeAhvfzc14849274 = nxKJxyyjJjnjAqgWjFeAhvfzc24423656;     nxKJxyyjJjnjAqgWjFeAhvfzc24423656 = nxKJxyyjJjnjAqgWjFeAhvfzc85244710;     nxKJxyyjJjnjAqgWjFeAhvfzc85244710 = nxKJxyyjJjnjAqgWjFeAhvfzc55117085;     nxKJxyyjJjnjAqgWjFeAhvfzc55117085 = nxKJxyyjJjnjAqgWjFeAhvfzc12446384;     nxKJxyyjJjnjAqgWjFeAhvfzc12446384 = nxKJxyyjJjnjAqgWjFeAhvfzc25669883;     nxKJxyyjJjnjAqgWjFeAhvfzc25669883 = nxKJxyyjJjnjAqgWjFeAhvfzc11706469;     nxKJxyyjJjnjAqgWjFeAhvfzc11706469 = nxKJxyyjJjnjAqgWjFeAhvfzc24118254;     nxKJxyyjJjnjAqgWjFeAhvfzc24118254 = nxKJxyyjJjnjAqgWjFeAhvfzc62251054;     nxKJxyyjJjnjAqgWjFeAhvfzc62251054 = nxKJxyyjJjnjAqgWjFeAhvfzc39594102;     nxKJxyyjJjnjAqgWjFeAhvfzc39594102 = nxKJxyyjJjnjAqgWjFeAhvfzc54077150;     nxKJxyyjJjnjAqgWjFeAhvfzc54077150 = nxKJxyyjJjnjAqgWjFeAhvfzc7092783;     nxKJxyyjJjnjAqgWjFeAhvfzc7092783 = nxKJxyyjJjnjAqgWjFeAhvfzc77540996;     nxKJxyyjJjnjAqgWjFeAhvfzc77540996 = nxKJxyyjJjnjAqgWjFeAhvfzc8725582;     nxKJxyyjJjnjAqgWjFeAhvfzc8725582 = nxKJxyyjJjnjAqgWjFeAhvfzc27890566;     nxKJxyyjJjnjAqgWjFeAhvfzc27890566 = nxKJxyyjJjnjAqgWjFeAhvfzc68673388;     nxKJxyyjJjnjAqgWjFeAhvfzc68673388 = nxKJxyyjJjnjAqgWjFeAhvfzc69190968;     nxKJxyyjJjnjAqgWjFeAhvfzc69190968 = nxKJxyyjJjnjAqgWjFeAhvfzc3583180;     nxKJxyyjJjnjAqgWjFeAhvfzc3583180 = nxKJxyyjJjnjAqgWjFeAhvfzc8527108;     nxKJxyyjJjnjAqgWjFeAhvfzc8527108 = nxKJxyyjJjnjAqgWjFeAhvfzc48397984;     nxKJxyyjJjnjAqgWjFeAhvfzc48397984 = nxKJxyyjJjnjAqgWjFeAhvfzc74182433;     nxKJxyyjJjnjAqgWjFeAhvfzc74182433 = nxKJxyyjJjnjAqgWjFeAhvfzc69496282;     nxKJxyyjJjnjAqgWjFeAhvfzc69496282 = nxKJxyyjJjnjAqgWjFeAhvfzc51120321;     nxKJxyyjJjnjAqgWjFeAhvfzc51120321 = nxKJxyyjJjnjAqgWjFeAhvfzc5408528;     nxKJxyyjJjnjAqgWjFeAhvfzc5408528 = nxKJxyyjJjnjAqgWjFeAhvfzc98566777;     nxKJxyyjJjnjAqgWjFeAhvfzc98566777 = nxKJxyyjJjnjAqgWjFeAhvfzc79865256;     nxKJxyyjJjnjAqgWjFeAhvfzc79865256 = nxKJxyyjJjnjAqgWjFeAhvfzc23498443;     nxKJxyyjJjnjAqgWjFeAhvfzc23498443 = nxKJxyyjJjnjAqgWjFeAhvfzc9929023;     nxKJxyyjJjnjAqgWjFeAhvfzc9929023 = nxKJxyyjJjnjAqgWjFeAhvfzc83408209;     nxKJxyyjJjnjAqgWjFeAhvfzc83408209 = nxKJxyyjJjnjAqgWjFeAhvfzc72357422;     nxKJxyyjJjnjAqgWjFeAhvfzc72357422 = nxKJxyyjJjnjAqgWjFeAhvfzc61085691;     nxKJxyyjJjnjAqgWjFeAhvfzc61085691 = nxKJxyyjJjnjAqgWjFeAhvfzc91885557;     nxKJxyyjJjnjAqgWjFeAhvfzc91885557 = nxKJxyyjJjnjAqgWjFeAhvfzc95853337;     nxKJxyyjJjnjAqgWjFeAhvfzc95853337 = nxKJxyyjJjnjAqgWjFeAhvfzc44376637;     nxKJxyyjJjnjAqgWjFeAhvfzc44376637 = nxKJxyyjJjnjAqgWjFeAhvfzc84992715;     nxKJxyyjJjnjAqgWjFeAhvfzc84992715 = nxKJxyyjJjnjAqgWjFeAhvfzc92675253;     nxKJxyyjJjnjAqgWjFeAhvfzc92675253 = nxKJxyyjJjnjAqgWjFeAhvfzc15583868;     nxKJxyyjJjnjAqgWjFeAhvfzc15583868 = nxKJxyyjJjnjAqgWjFeAhvfzc31511100;     nxKJxyyjJjnjAqgWjFeAhvfzc31511100 = nxKJxyyjJjnjAqgWjFeAhvfzc79566564;     nxKJxyyjJjnjAqgWjFeAhvfzc79566564 = nxKJxyyjJjnjAqgWjFeAhvfzc62568618;     nxKJxyyjJjnjAqgWjFeAhvfzc62568618 = nxKJxyyjJjnjAqgWjFeAhvfzc87648771;     nxKJxyyjJjnjAqgWjFeAhvfzc87648771 = nxKJxyyjJjnjAqgWjFeAhvfzc85727149;     nxKJxyyjJjnjAqgWjFeAhvfzc85727149 = nxKJxyyjJjnjAqgWjFeAhvfzc14637045;     nxKJxyyjJjnjAqgWjFeAhvfzc14637045 = nxKJxyyjJjnjAqgWjFeAhvfzc29454793;     nxKJxyyjJjnjAqgWjFeAhvfzc29454793 = nxKJxyyjJjnjAqgWjFeAhvfzc30127793;     nxKJxyyjJjnjAqgWjFeAhvfzc30127793 = nxKJxyyjJjnjAqgWjFeAhvfzc44456933;     nxKJxyyjJjnjAqgWjFeAhvfzc44456933 = nxKJxyyjJjnjAqgWjFeAhvfzc70155642;     nxKJxyyjJjnjAqgWjFeAhvfzc70155642 = nxKJxyyjJjnjAqgWjFeAhvfzc76902117;     nxKJxyyjJjnjAqgWjFeAhvfzc76902117 = nxKJxyyjJjnjAqgWjFeAhvfzc65624502;     nxKJxyyjJjnjAqgWjFeAhvfzc65624502 = nxKJxyyjJjnjAqgWjFeAhvfzc61457248;     nxKJxyyjJjnjAqgWjFeAhvfzc61457248 = nxKJxyyjJjnjAqgWjFeAhvfzc5994354;     nxKJxyyjJjnjAqgWjFeAhvfzc5994354 = nxKJxyyjJjnjAqgWjFeAhvfzc40406300;     nxKJxyyjJjnjAqgWjFeAhvfzc40406300 = nxKJxyyjJjnjAqgWjFeAhvfzc67501918;     nxKJxyyjJjnjAqgWjFeAhvfzc67501918 = nxKJxyyjJjnjAqgWjFeAhvfzc76567855;     nxKJxyyjJjnjAqgWjFeAhvfzc76567855 = nxKJxyyjJjnjAqgWjFeAhvfzc75688140;     nxKJxyyjJjnjAqgWjFeAhvfzc75688140 = nxKJxyyjJjnjAqgWjFeAhvfzc45352992;     nxKJxyyjJjnjAqgWjFeAhvfzc45352992 = nxKJxyyjJjnjAqgWjFeAhvfzc73303335;     nxKJxyyjJjnjAqgWjFeAhvfzc73303335 = nxKJxyyjJjnjAqgWjFeAhvfzc79836182;     nxKJxyyjJjnjAqgWjFeAhvfzc79836182 = nxKJxyyjJjnjAqgWjFeAhvfzc56550307;     nxKJxyyjJjnjAqgWjFeAhvfzc56550307 = nxKJxyyjJjnjAqgWjFeAhvfzc32581127;     nxKJxyyjJjnjAqgWjFeAhvfzc32581127 = nxKJxyyjJjnjAqgWjFeAhvfzc2171441;     nxKJxyyjJjnjAqgWjFeAhvfzc2171441 = nxKJxyyjJjnjAqgWjFeAhvfzc1777446;     nxKJxyyjJjnjAqgWjFeAhvfzc1777446 = nxKJxyyjJjnjAqgWjFeAhvfzc40710045;     nxKJxyyjJjnjAqgWjFeAhvfzc40710045 = nxKJxyyjJjnjAqgWjFeAhvfzc89893631;     nxKJxyyjJjnjAqgWjFeAhvfzc89893631 = nxKJxyyjJjnjAqgWjFeAhvfzc78508410;     nxKJxyyjJjnjAqgWjFeAhvfzc78508410 = nxKJxyyjJjnjAqgWjFeAhvfzc62191592;     nxKJxyyjJjnjAqgWjFeAhvfzc62191592 = nxKJxyyjJjnjAqgWjFeAhvfzc11239446;     nxKJxyyjJjnjAqgWjFeAhvfzc11239446 = nxKJxyyjJjnjAqgWjFeAhvfzc33164360;     nxKJxyyjJjnjAqgWjFeAhvfzc33164360 = nxKJxyyjJjnjAqgWjFeAhvfzc23732867;     nxKJxyyjJjnjAqgWjFeAhvfzc23732867 = nxKJxyyjJjnjAqgWjFeAhvfzc35215313;     nxKJxyyjJjnjAqgWjFeAhvfzc35215313 = nxKJxyyjJjnjAqgWjFeAhvfzc53089521;     nxKJxyyjJjnjAqgWjFeAhvfzc53089521 = nxKJxyyjJjnjAqgWjFeAhvfzc37679868;     nxKJxyyjJjnjAqgWjFeAhvfzc37679868 = nxKJxyyjJjnjAqgWjFeAhvfzc24016616;     nxKJxyyjJjnjAqgWjFeAhvfzc24016616 = nxKJxyyjJjnjAqgWjFeAhvfzc45958489;     nxKJxyyjJjnjAqgWjFeAhvfzc45958489 = nxKJxyyjJjnjAqgWjFeAhvfzc60749212;     nxKJxyyjJjnjAqgWjFeAhvfzc60749212 = nxKJxyyjJjnjAqgWjFeAhvfzc88455283;     nxKJxyyjJjnjAqgWjFeAhvfzc88455283 = nxKJxyyjJjnjAqgWjFeAhvfzc54859238;     nxKJxyyjJjnjAqgWjFeAhvfzc54859238 = nxKJxyyjJjnjAqgWjFeAhvfzc21665528;     nxKJxyyjJjnjAqgWjFeAhvfzc21665528 = nxKJxyyjJjnjAqgWjFeAhvfzc94247210;}
// Junk Finished
