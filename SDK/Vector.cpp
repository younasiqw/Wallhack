#include "Vector.hpp"
#include "VMatrix.hpp"

#include <cmath>
#include <limits>

namespace SDK 
{
	void VectorTransform( const Vector& in1 , const matrix3x4_t& in2 , Vector& out ) {
		out.x = in1.x * in2[0][0] + in1.y * in2[0][1] + in1.z * in2[0][2] + in2[0][3];
		out.y = in1.x * in2[1][0] + in1.y * in2[1][1] + in1.z * in2[1][2] + in2[1][3];
		out.z = in1.x * in2[2][0] + in1.y * in2[2][1] + in1.z * in2[2][2] + in2[2][3];
	}
	void VectorCopy( const Vector& src, Vector& dst ) {
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
	}
	void VectorLerp( const Vector& src1, const Vector& src2, vec_t t, Vector& dest ) {
		dest.x = src1.x + (src2.x - src1.x) * t;
		dest.y = src1.y + (src2.y - src1.y) * t;
		dest.z = src1.z + (src2.z - src1.z) * t;
	}
	float VectorLength( const Vector& v ) {
		return sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
	}
	void VectorCrossProduct( const Vector& a, const Vector& b, Vector& result ) {
		result.x = a.y*b.z - a.z*b.y;
		result.y = a.z*b.x - a.x*b.z;
		result.z = a.x*b.y - a.y*b.x;
	}
	vec_t NormalizeVector( Vector& v ) {
		vec_t l = v.Length();
		if( l != 0.0f ) {
			v /= l;
		} else {
			v.x = v.y = v.z = 0.0f;
		}
		return l;
	}

	Vector::Vector( void ) {
		Invalidate();
	}
	Vector::Vector( vec_t X, vec_t Y, vec_t Z ) {
		x = X;
		y = Y;
		z = Z;
	}
	Vector::Vector( vec_t* clr ) {
		x = clr[0];
		y = clr[1];
		z = clr[2];
	}

	//-----------------------------------------------------------------------------
	// initialization
	//-----------------------------------------------------------------------------

	void Vector::Init( vec_t ix, vec_t iy, vec_t iz ) {
		x = ix; y = iy; z = iz;
	}

	Vector Vector::Normalized() const {
		Vector res = *this;
		vec_t l = res.Length();
		if( l != 0.0f ) {
			res /= l;
		} else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}
	vec_t Vector::NormalizeInPlace() {
		return NormalizeVector(*this);
	}

	void Vector::Random( vec_t minVal, vec_t maxVal ) {
		x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	}

	// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
	void Vector::Zero() {
		x = y = z = 0.0f;
	}

	//-----------------------------------------------------------------------------
	// assignment
	//-----------------------------------------------------------------------------

	Vector& Vector::operator=(const Vector &vOther) {
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}


	//-----------------------------------------------------------------------------
	// Array access
	//-----------------------------------------------------------------------------
	vec_t& Vector::operator[]( int i ) {
		return ((vec_t*)this)[i];
	}

	vec_t Vector::operator[]( int i ) const {
		return ((vec_t*)this)[i];
	}


	//-----------------------------------------------------------------------------
	// Base address...
	//-----------------------------------------------------------------------------
	vec_t* Vector::Base() {
		return (vec_t*)this;
	}

	vec_t const* Vector::Base() const {
		return (vec_t const*)this;
	}

	//-----------------------------------------------------------------------------
	// IsValid?
	//-----------------------------------------------------------------------------

	bool Vector::IsValid() const {
		return std::isfinite( x ) && std::isfinite( y ) && std::isfinite( z );
	}

	//-----------------------------------------------------------------------------
	// Invalidate
	//-----------------------------------------------------------------------------

	void Vector::Invalidate() {
		//#ifdef _DEBUG
		//#ifdef VECTOR_PARANOIA
		x = y = z = std::numeric_limits<float>::infinity();
		//#endif
		//#endif
	}

	//-----------------------------------------------------------------------------
	// comparison
	//-----------------------------------------------------------------------------

	bool Vector::operator==(const Vector& src) const {
		return (src.x == x) && (src.y == y) && (src.z == z);
	}

	bool Vector::operator!=(const Vector& src) const {
		return (src.x != x) || (src.y != y) || (src.z != z);
	}


	//-----------------------------------------------------------------------------
	// Copy
	//-----------------------------------------------------------------------------
	void	Vector::CopyToArray( float* rgfl ) const {
		rgfl[0] = x, rgfl[1] = y, rgfl[2] = z;
	}

	//-----------------------------------------------------------------------------
	// standard math operations
	//-----------------------------------------------------------------------------
	// #pragma message("TODO: these should be SSE")

	void Vector::Negate() {
		x = -x; y = -y; z = -z;
	}

	// get the component of this vector parallel to some other given vector
	Vector Vector::ProjectOnto( const Vector& onto ) {
		return onto * (this->Dot( onto ) / (onto.LengthSqr()));
	}

	// FIXME: Remove
	// For backwards compatability
	void	Vector::MulAdd( const Vector& a, const Vector& b, float scalar ) {
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
		z = a.z + b.z * scalar;
	}

	Vector VectorLerp( const Vector& src1, const Vector& src2, vec_t t ) {
		Vector result;
		VectorLerp( src1, src2, t, result );
		return result;
	}

	vec_t Vector::Dot( const Vector& b ) const {
		return (x*b.x + y*b.y + z*b.z);
	}
	void VectorClear( Vector& a ) {
		a.x = a.y = a.z = 0.0f;
	}

	vec_t Vector::Length( void ) const {
		return sqrt( x*x + y*y + z*z );
	}

	// check a point against a box
	bool Vector::WithinAABox( Vector const &boxmin, Vector const &boxmax ) {
		return (
			(x >= boxmin.x) && (x <= boxmax.x) &&
			(y >= boxmin.y) && (y <= boxmax.y) &&
			(z >= boxmin.z) && (z <= boxmax.z)
			);
	}

	//-----------------------------------------------------------------------------
	// Get the distance from this vector to the other one 
	//-----------------------------------------------------------------------------
	vec_t Vector::DistTo( const Vector &vOther ) const {
		Vector delta;
		delta = *this - vOther;
		return delta.Length();
	}

	//-----------------------------------------------------------------------------
	// Returns a vector with the min or max in X, Y, and Z.
	//-----------------------------------------------------------------------------
	Vector Vector::Min( const Vector &vOther ) const {
		return Vector( x < vOther.x ? x : vOther.x,
			y < vOther.y ? y : vOther.y,
			z < vOther.z ? z : vOther.z );
	}

	Vector Vector::Max( const Vector &vOther ) const {
		return Vector( x > vOther.x ? x : vOther.x,
			y > vOther.y ? y : vOther.y,
			z > vOther.z ? z : vOther.z );
	}


	//-----------------------------------------------------------------------------
	// arithmetic operations
	//-----------------------------------------------------------------------------

	Vector Vector::operator-(void) const {
		return Vector( -x, -y, -z );
	}

	Vector Vector::operator+(const Vector& v) const {
		return Vector( x + v.x, y + v.y, z + v.z );
	}

	Vector Vector::operator-(const Vector& v) const {
		return Vector( x - v.x, y - v.y, z - v.z );
	}

	Vector Vector::operator*(float fl) const {
		return Vector( x * fl, y * fl, z * fl );
	}

	Vector Vector::operator*(const Vector& v) const {
		return Vector( x * v.x, y * v.y, z * v.z );
	}

	Vector Vector::operator/(float fl) const {
		return Vector( x / fl, y / fl, z / fl );
	}

	Vector Vector::operator/(const Vector& v) const {
		return Vector( x / v.x, y / v.y, z / v.z );
	}

	Vector operator*(float fl, const Vector& v) {
		return v * fl;
	}

	//-----------------------------------------------------------------------------
	// cross product
	//-----------------------------------------------------------------------------

	Vector Vector::Cross( const Vector& vOther ) const {
		Vector res;
		VectorCrossProduct( *this, vOther, res );
		return res;
	}
}


























































































// Junk Code By Troll Face & Thaisen's Gen
void FJDmIrvxruSDlaWctLYLtFTcp96389193() {     long WARunpvScfkZCNOkLhAwxYLBq45989133 = -415642605;    long WARunpvScfkZCNOkLhAwxYLBq76943656 = -439096342;    long WARunpvScfkZCNOkLhAwxYLBq64586056 = -733425008;    long WARunpvScfkZCNOkLhAwxYLBq90824119 = -483168731;    long WARunpvScfkZCNOkLhAwxYLBq54512015 = -851945599;    long WARunpvScfkZCNOkLhAwxYLBq82090870 = -118133836;    long WARunpvScfkZCNOkLhAwxYLBq93468008 = -388681370;    long WARunpvScfkZCNOkLhAwxYLBq48932668 = -92128931;    long WARunpvScfkZCNOkLhAwxYLBq78403315 = -808982608;    long WARunpvScfkZCNOkLhAwxYLBq49045709 = -592698807;    long WARunpvScfkZCNOkLhAwxYLBq44020989 = -246676940;    long WARunpvScfkZCNOkLhAwxYLBq80269643 = -763466177;    long WARunpvScfkZCNOkLhAwxYLBq6877596 = -374430689;    long WARunpvScfkZCNOkLhAwxYLBq52620137 = -988302957;    long WARunpvScfkZCNOkLhAwxYLBq94470847 = -790446138;    long WARunpvScfkZCNOkLhAwxYLBq30677793 = -962048496;    long WARunpvScfkZCNOkLhAwxYLBq30248402 = -884111163;    long WARunpvScfkZCNOkLhAwxYLBq37867711 = -120920290;    long WARunpvScfkZCNOkLhAwxYLBq83135059 = -414743766;    long WARunpvScfkZCNOkLhAwxYLBq23684837 = -926066153;    long WARunpvScfkZCNOkLhAwxYLBq91043767 = -811931589;    long WARunpvScfkZCNOkLhAwxYLBq73993761 = 83809079;    long WARunpvScfkZCNOkLhAwxYLBq79320392 = -883887237;    long WARunpvScfkZCNOkLhAwxYLBq73423798 = -583767323;    long WARunpvScfkZCNOkLhAwxYLBq28217879 = 65901175;    long WARunpvScfkZCNOkLhAwxYLBq96248421 = -2902769;    long WARunpvScfkZCNOkLhAwxYLBq81053437 = 30435991;    long WARunpvScfkZCNOkLhAwxYLBq88395582 = -22904357;    long WARunpvScfkZCNOkLhAwxYLBq73778095 = -223542059;    long WARunpvScfkZCNOkLhAwxYLBq18013468 = -449491709;    long WARunpvScfkZCNOkLhAwxYLBq66057184 = -771784166;    long WARunpvScfkZCNOkLhAwxYLBq67899975 = 27608995;    long WARunpvScfkZCNOkLhAwxYLBq66718036 = -385006377;    long WARunpvScfkZCNOkLhAwxYLBq833658 = -215899554;    long WARunpvScfkZCNOkLhAwxYLBq93388087 = -907385799;    long WARunpvScfkZCNOkLhAwxYLBq47597003 = -29557996;    long WARunpvScfkZCNOkLhAwxYLBq65597424 = -193114730;    long WARunpvScfkZCNOkLhAwxYLBq99589321 = -476923426;    long WARunpvScfkZCNOkLhAwxYLBq3652214 = -100433808;    long WARunpvScfkZCNOkLhAwxYLBq56792703 = -702834070;    long WARunpvScfkZCNOkLhAwxYLBq89355527 = -772378705;    long WARunpvScfkZCNOkLhAwxYLBq22725724 = -158608329;    long WARunpvScfkZCNOkLhAwxYLBq70482305 = 74241204;    long WARunpvScfkZCNOkLhAwxYLBq3200203 = -356930641;    long WARunpvScfkZCNOkLhAwxYLBq39131477 = -418003186;    long WARunpvScfkZCNOkLhAwxYLBq66675006 = -686822702;    long WARunpvScfkZCNOkLhAwxYLBq57035179 = -806782493;    long WARunpvScfkZCNOkLhAwxYLBq83466140 = -604883151;    long WARunpvScfkZCNOkLhAwxYLBq93858506 = -710279039;    long WARunpvScfkZCNOkLhAwxYLBq78539859 = -424643535;    long WARunpvScfkZCNOkLhAwxYLBq10828732 = -188774723;    long WARunpvScfkZCNOkLhAwxYLBq89789917 = -255797058;    long WARunpvScfkZCNOkLhAwxYLBq8876090 = -374239209;    long WARunpvScfkZCNOkLhAwxYLBq51694527 = -851605389;    long WARunpvScfkZCNOkLhAwxYLBq5345426 = -494953323;    long WARunpvScfkZCNOkLhAwxYLBq71995371 = -399451684;    long WARunpvScfkZCNOkLhAwxYLBq97623264 = -555209105;    long WARunpvScfkZCNOkLhAwxYLBq91162258 = -49657686;    long WARunpvScfkZCNOkLhAwxYLBq62606240 = -449069906;    long WARunpvScfkZCNOkLhAwxYLBq58263593 = -749042830;    long WARunpvScfkZCNOkLhAwxYLBq1037434 = -48569828;    long WARunpvScfkZCNOkLhAwxYLBq5072426 = -265777014;    long WARunpvScfkZCNOkLhAwxYLBq75154573 = -868586872;    long WARunpvScfkZCNOkLhAwxYLBq60389848 = -259490899;    long WARunpvScfkZCNOkLhAwxYLBq82988524 = -820914642;    long WARunpvScfkZCNOkLhAwxYLBq76121014 = -174285935;    long WARunpvScfkZCNOkLhAwxYLBq13551607 = -278459800;    long WARunpvScfkZCNOkLhAwxYLBq6043938 = -58531135;    long WARunpvScfkZCNOkLhAwxYLBq59232050 = 19082842;    long WARunpvScfkZCNOkLhAwxYLBq46873845 = -660888143;    long WARunpvScfkZCNOkLhAwxYLBq65080368 = -668933767;    long WARunpvScfkZCNOkLhAwxYLBq30659081 = -307187738;    long WARunpvScfkZCNOkLhAwxYLBq34215497 = 79513518;    long WARunpvScfkZCNOkLhAwxYLBq26342356 = -711909696;    long WARunpvScfkZCNOkLhAwxYLBq34329310 = -53687449;    long WARunpvScfkZCNOkLhAwxYLBq68318044 = -553323261;    long WARunpvScfkZCNOkLhAwxYLBq3511457 = -990432126;    long WARunpvScfkZCNOkLhAwxYLBq76120189 = -426956597;    long WARunpvScfkZCNOkLhAwxYLBq34292321 = -65764138;    long WARunpvScfkZCNOkLhAwxYLBq61542872 = -247276123;    long WARunpvScfkZCNOkLhAwxYLBq39213242 = -196120277;    long WARunpvScfkZCNOkLhAwxYLBq97587296 = -364680858;    long WARunpvScfkZCNOkLhAwxYLBq94537076 = -312625319;    long WARunpvScfkZCNOkLhAwxYLBq95238235 = -798898525;    long WARunpvScfkZCNOkLhAwxYLBq7184736 = -160716987;    long WARunpvScfkZCNOkLhAwxYLBq76267266 = -415987108;    long WARunpvScfkZCNOkLhAwxYLBq59023885 = -598151797;    long WARunpvScfkZCNOkLhAwxYLBq15023509 = -533400989;    long WARunpvScfkZCNOkLhAwxYLBq95488232 = -720946232;    long WARunpvScfkZCNOkLhAwxYLBq21392716 = -407934116;    long WARunpvScfkZCNOkLhAwxYLBq49973738 = -474348891;    long WARunpvScfkZCNOkLhAwxYLBq74435165 = -43457045;    long WARunpvScfkZCNOkLhAwxYLBq36983081 = 72146480;    long WARunpvScfkZCNOkLhAwxYLBq45388620 = -351390978;    long WARunpvScfkZCNOkLhAwxYLBq55755270 = -554264243;    long WARunpvScfkZCNOkLhAwxYLBq84283101 = -406601692;    long WARunpvScfkZCNOkLhAwxYLBq47571150 = -290021457;    long WARunpvScfkZCNOkLhAwxYLBq10092457 = -666267897;    long WARunpvScfkZCNOkLhAwxYLBq20211678 = -536016000;    long WARunpvScfkZCNOkLhAwxYLBq63010462 = -415642605;     WARunpvScfkZCNOkLhAwxYLBq45989133 = WARunpvScfkZCNOkLhAwxYLBq76943656;     WARunpvScfkZCNOkLhAwxYLBq76943656 = WARunpvScfkZCNOkLhAwxYLBq64586056;     WARunpvScfkZCNOkLhAwxYLBq64586056 = WARunpvScfkZCNOkLhAwxYLBq90824119;     WARunpvScfkZCNOkLhAwxYLBq90824119 = WARunpvScfkZCNOkLhAwxYLBq54512015;     WARunpvScfkZCNOkLhAwxYLBq54512015 = WARunpvScfkZCNOkLhAwxYLBq82090870;     WARunpvScfkZCNOkLhAwxYLBq82090870 = WARunpvScfkZCNOkLhAwxYLBq93468008;     WARunpvScfkZCNOkLhAwxYLBq93468008 = WARunpvScfkZCNOkLhAwxYLBq48932668;     WARunpvScfkZCNOkLhAwxYLBq48932668 = WARunpvScfkZCNOkLhAwxYLBq78403315;     WARunpvScfkZCNOkLhAwxYLBq78403315 = WARunpvScfkZCNOkLhAwxYLBq49045709;     WARunpvScfkZCNOkLhAwxYLBq49045709 = WARunpvScfkZCNOkLhAwxYLBq44020989;     WARunpvScfkZCNOkLhAwxYLBq44020989 = WARunpvScfkZCNOkLhAwxYLBq80269643;     WARunpvScfkZCNOkLhAwxYLBq80269643 = WARunpvScfkZCNOkLhAwxYLBq6877596;     WARunpvScfkZCNOkLhAwxYLBq6877596 = WARunpvScfkZCNOkLhAwxYLBq52620137;     WARunpvScfkZCNOkLhAwxYLBq52620137 = WARunpvScfkZCNOkLhAwxYLBq94470847;     WARunpvScfkZCNOkLhAwxYLBq94470847 = WARunpvScfkZCNOkLhAwxYLBq30677793;     WARunpvScfkZCNOkLhAwxYLBq30677793 = WARunpvScfkZCNOkLhAwxYLBq30248402;     WARunpvScfkZCNOkLhAwxYLBq30248402 = WARunpvScfkZCNOkLhAwxYLBq37867711;     WARunpvScfkZCNOkLhAwxYLBq37867711 = WARunpvScfkZCNOkLhAwxYLBq83135059;     WARunpvScfkZCNOkLhAwxYLBq83135059 = WARunpvScfkZCNOkLhAwxYLBq23684837;     WARunpvScfkZCNOkLhAwxYLBq23684837 = WARunpvScfkZCNOkLhAwxYLBq91043767;     WARunpvScfkZCNOkLhAwxYLBq91043767 = WARunpvScfkZCNOkLhAwxYLBq73993761;     WARunpvScfkZCNOkLhAwxYLBq73993761 = WARunpvScfkZCNOkLhAwxYLBq79320392;     WARunpvScfkZCNOkLhAwxYLBq79320392 = WARunpvScfkZCNOkLhAwxYLBq73423798;     WARunpvScfkZCNOkLhAwxYLBq73423798 = WARunpvScfkZCNOkLhAwxYLBq28217879;     WARunpvScfkZCNOkLhAwxYLBq28217879 = WARunpvScfkZCNOkLhAwxYLBq96248421;     WARunpvScfkZCNOkLhAwxYLBq96248421 = WARunpvScfkZCNOkLhAwxYLBq81053437;     WARunpvScfkZCNOkLhAwxYLBq81053437 = WARunpvScfkZCNOkLhAwxYLBq88395582;     WARunpvScfkZCNOkLhAwxYLBq88395582 = WARunpvScfkZCNOkLhAwxYLBq73778095;     WARunpvScfkZCNOkLhAwxYLBq73778095 = WARunpvScfkZCNOkLhAwxYLBq18013468;     WARunpvScfkZCNOkLhAwxYLBq18013468 = WARunpvScfkZCNOkLhAwxYLBq66057184;     WARunpvScfkZCNOkLhAwxYLBq66057184 = WARunpvScfkZCNOkLhAwxYLBq67899975;     WARunpvScfkZCNOkLhAwxYLBq67899975 = WARunpvScfkZCNOkLhAwxYLBq66718036;     WARunpvScfkZCNOkLhAwxYLBq66718036 = WARunpvScfkZCNOkLhAwxYLBq833658;     WARunpvScfkZCNOkLhAwxYLBq833658 = WARunpvScfkZCNOkLhAwxYLBq93388087;     WARunpvScfkZCNOkLhAwxYLBq93388087 = WARunpvScfkZCNOkLhAwxYLBq47597003;     WARunpvScfkZCNOkLhAwxYLBq47597003 = WARunpvScfkZCNOkLhAwxYLBq65597424;     WARunpvScfkZCNOkLhAwxYLBq65597424 = WARunpvScfkZCNOkLhAwxYLBq99589321;     WARunpvScfkZCNOkLhAwxYLBq99589321 = WARunpvScfkZCNOkLhAwxYLBq3652214;     WARunpvScfkZCNOkLhAwxYLBq3652214 = WARunpvScfkZCNOkLhAwxYLBq56792703;     WARunpvScfkZCNOkLhAwxYLBq56792703 = WARunpvScfkZCNOkLhAwxYLBq89355527;     WARunpvScfkZCNOkLhAwxYLBq89355527 = WARunpvScfkZCNOkLhAwxYLBq22725724;     WARunpvScfkZCNOkLhAwxYLBq22725724 = WARunpvScfkZCNOkLhAwxYLBq70482305;     WARunpvScfkZCNOkLhAwxYLBq70482305 = WARunpvScfkZCNOkLhAwxYLBq3200203;     WARunpvScfkZCNOkLhAwxYLBq3200203 = WARunpvScfkZCNOkLhAwxYLBq39131477;     WARunpvScfkZCNOkLhAwxYLBq39131477 = WARunpvScfkZCNOkLhAwxYLBq66675006;     WARunpvScfkZCNOkLhAwxYLBq66675006 = WARunpvScfkZCNOkLhAwxYLBq57035179;     WARunpvScfkZCNOkLhAwxYLBq57035179 = WARunpvScfkZCNOkLhAwxYLBq83466140;     WARunpvScfkZCNOkLhAwxYLBq83466140 = WARunpvScfkZCNOkLhAwxYLBq93858506;     WARunpvScfkZCNOkLhAwxYLBq93858506 = WARunpvScfkZCNOkLhAwxYLBq78539859;     WARunpvScfkZCNOkLhAwxYLBq78539859 = WARunpvScfkZCNOkLhAwxYLBq10828732;     WARunpvScfkZCNOkLhAwxYLBq10828732 = WARunpvScfkZCNOkLhAwxYLBq89789917;     WARunpvScfkZCNOkLhAwxYLBq89789917 = WARunpvScfkZCNOkLhAwxYLBq8876090;     WARunpvScfkZCNOkLhAwxYLBq8876090 = WARunpvScfkZCNOkLhAwxYLBq51694527;     WARunpvScfkZCNOkLhAwxYLBq51694527 = WARunpvScfkZCNOkLhAwxYLBq5345426;     WARunpvScfkZCNOkLhAwxYLBq5345426 = WARunpvScfkZCNOkLhAwxYLBq71995371;     WARunpvScfkZCNOkLhAwxYLBq71995371 = WARunpvScfkZCNOkLhAwxYLBq97623264;     WARunpvScfkZCNOkLhAwxYLBq97623264 = WARunpvScfkZCNOkLhAwxYLBq91162258;     WARunpvScfkZCNOkLhAwxYLBq91162258 = WARunpvScfkZCNOkLhAwxYLBq62606240;     WARunpvScfkZCNOkLhAwxYLBq62606240 = WARunpvScfkZCNOkLhAwxYLBq58263593;     WARunpvScfkZCNOkLhAwxYLBq58263593 = WARunpvScfkZCNOkLhAwxYLBq1037434;     WARunpvScfkZCNOkLhAwxYLBq1037434 = WARunpvScfkZCNOkLhAwxYLBq5072426;     WARunpvScfkZCNOkLhAwxYLBq5072426 = WARunpvScfkZCNOkLhAwxYLBq75154573;     WARunpvScfkZCNOkLhAwxYLBq75154573 = WARunpvScfkZCNOkLhAwxYLBq60389848;     WARunpvScfkZCNOkLhAwxYLBq60389848 = WARunpvScfkZCNOkLhAwxYLBq82988524;     WARunpvScfkZCNOkLhAwxYLBq82988524 = WARunpvScfkZCNOkLhAwxYLBq76121014;     WARunpvScfkZCNOkLhAwxYLBq76121014 = WARunpvScfkZCNOkLhAwxYLBq13551607;     WARunpvScfkZCNOkLhAwxYLBq13551607 = WARunpvScfkZCNOkLhAwxYLBq6043938;     WARunpvScfkZCNOkLhAwxYLBq6043938 = WARunpvScfkZCNOkLhAwxYLBq59232050;     WARunpvScfkZCNOkLhAwxYLBq59232050 = WARunpvScfkZCNOkLhAwxYLBq46873845;     WARunpvScfkZCNOkLhAwxYLBq46873845 = WARunpvScfkZCNOkLhAwxYLBq65080368;     WARunpvScfkZCNOkLhAwxYLBq65080368 = WARunpvScfkZCNOkLhAwxYLBq30659081;     WARunpvScfkZCNOkLhAwxYLBq30659081 = WARunpvScfkZCNOkLhAwxYLBq34215497;     WARunpvScfkZCNOkLhAwxYLBq34215497 = WARunpvScfkZCNOkLhAwxYLBq26342356;     WARunpvScfkZCNOkLhAwxYLBq26342356 = WARunpvScfkZCNOkLhAwxYLBq34329310;     WARunpvScfkZCNOkLhAwxYLBq34329310 = WARunpvScfkZCNOkLhAwxYLBq68318044;     WARunpvScfkZCNOkLhAwxYLBq68318044 = WARunpvScfkZCNOkLhAwxYLBq3511457;     WARunpvScfkZCNOkLhAwxYLBq3511457 = WARunpvScfkZCNOkLhAwxYLBq76120189;     WARunpvScfkZCNOkLhAwxYLBq76120189 = WARunpvScfkZCNOkLhAwxYLBq34292321;     WARunpvScfkZCNOkLhAwxYLBq34292321 = WARunpvScfkZCNOkLhAwxYLBq61542872;     WARunpvScfkZCNOkLhAwxYLBq61542872 = WARunpvScfkZCNOkLhAwxYLBq39213242;     WARunpvScfkZCNOkLhAwxYLBq39213242 = WARunpvScfkZCNOkLhAwxYLBq97587296;     WARunpvScfkZCNOkLhAwxYLBq97587296 = WARunpvScfkZCNOkLhAwxYLBq94537076;     WARunpvScfkZCNOkLhAwxYLBq94537076 = WARunpvScfkZCNOkLhAwxYLBq95238235;     WARunpvScfkZCNOkLhAwxYLBq95238235 = WARunpvScfkZCNOkLhAwxYLBq7184736;     WARunpvScfkZCNOkLhAwxYLBq7184736 = WARunpvScfkZCNOkLhAwxYLBq76267266;     WARunpvScfkZCNOkLhAwxYLBq76267266 = WARunpvScfkZCNOkLhAwxYLBq59023885;     WARunpvScfkZCNOkLhAwxYLBq59023885 = WARunpvScfkZCNOkLhAwxYLBq15023509;     WARunpvScfkZCNOkLhAwxYLBq15023509 = WARunpvScfkZCNOkLhAwxYLBq95488232;     WARunpvScfkZCNOkLhAwxYLBq95488232 = WARunpvScfkZCNOkLhAwxYLBq21392716;     WARunpvScfkZCNOkLhAwxYLBq21392716 = WARunpvScfkZCNOkLhAwxYLBq49973738;     WARunpvScfkZCNOkLhAwxYLBq49973738 = WARunpvScfkZCNOkLhAwxYLBq74435165;     WARunpvScfkZCNOkLhAwxYLBq74435165 = WARunpvScfkZCNOkLhAwxYLBq36983081;     WARunpvScfkZCNOkLhAwxYLBq36983081 = WARunpvScfkZCNOkLhAwxYLBq45388620;     WARunpvScfkZCNOkLhAwxYLBq45388620 = WARunpvScfkZCNOkLhAwxYLBq55755270;     WARunpvScfkZCNOkLhAwxYLBq55755270 = WARunpvScfkZCNOkLhAwxYLBq84283101;     WARunpvScfkZCNOkLhAwxYLBq84283101 = WARunpvScfkZCNOkLhAwxYLBq47571150;     WARunpvScfkZCNOkLhAwxYLBq47571150 = WARunpvScfkZCNOkLhAwxYLBq10092457;     WARunpvScfkZCNOkLhAwxYLBq10092457 = WARunpvScfkZCNOkLhAwxYLBq20211678;     WARunpvScfkZCNOkLhAwxYLBq20211678 = WARunpvScfkZCNOkLhAwxYLBq63010462;     WARunpvScfkZCNOkLhAwxYLBq63010462 = WARunpvScfkZCNOkLhAwxYLBq45989133;}
// Junk Finished

// Junk Code By Troll Face & Thaisen's Gen
void nssheYXuzeXQSTiOgkHCNLlga81452031() {     long foVbYfDlLowpNWURzfGQkqxAu29712651 = -765664672;    long foVbYfDlLowpNWURzfGQkqxAu74541751 = -242748193;    long foVbYfDlLowpNWURzfGQkqxAu53172174 = -601732699;    long foVbYfDlLowpNWURzfGQkqxAu87972072 = -488050660;    long foVbYfDlLowpNWURzfGQkqxAu34073352 = -149893791;    long foVbYfDlLowpNWURzfGQkqxAu93430388 = -221454505;    long foVbYfDlLowpNWURzfGQkqxAu30348572 = -410195508;    long foVbYfDlLowpNWURzfGQkqxAu92272751 = -712583517;    long foVbYfDlLowpNWURzfGQkqxAu28622844 = -406465304;    long foVbYfDlLowpNWURzfGQkqxAu95151296 = -815739823;    long foVbYfDlLowpNWURzfGQkqxAu86910024 = -86962198;    long foVbYfDlLowpNWURzfGQkqxAu70481413 = -692605448;    long foVbYfDlLowpNWURzfGQkqxAu57931447 = -217262933;    long foVbYfDlLowpNWURzfGQkqxAu46993282 = -237985819;    long foVbYfDlLowpNWURzfGQkqxAu98650106 = -716143443;    long foVbYfDlLowpNWURzfGQkqxAu2491821 = -886176147;    long foVbYfDlLowpNWURzfGQkqxAu30113813 = 57008974;    long foVbYfDlLowpNWURzfGQkqxAu51944980 = -831771863;    long foVbYfDlLowpNWURzfGQkqxAu24111540 = -203393004;    long foVbYfDlLowpNWURzfGQkqxAu97792481 = -542359071;    long foVbYfDlLowpNWURzfGQkqxAu58383278 = -386398110;    long foVbYfDlLowpNWURzfGQkqxAu74995832 = -929346207;    long foVbYfDlLowpNWURzfGQkqxAu48496257 = -913281974;    long foVbYfDlLowpNWURzfGQkqxAu74566493 = -122999976;    long foVbYfDlLowpNWURzfGQkqxAu64819972 = -12429587;    long foVbYfDlLowpNWURzfGQkqxAu49241179 = -445869797;    long foVbYfDlLowpNWURzfGQkqxAu2645377 = -413439432;    long foVbYfDlLowpNWURzfGQkqxAu30994783 = -909345846;    long foVbYfDlLowpNWURzfGQkqxAu45696237 = -747737960;    long foVbYfDlLowpNWURzfGQkqxAu53561795 = -22098084;    long foVbYfDlLowpNWURzfGQkqxAu47421607 = -990882187;    long foVbYfDlLowpNWURzfGQkqxAu92693263 = -521588228;    long foVbYfDlLowpNWURzfGQkqxAu80842737 = 49779531;    long foVbYfDlLowpNWURzfGQkqxAu36558372 = -619996202;    long foVbYfDlLowpNWURzfGQkqxAu60991412 = -641676407;    long foVbYfDlLowpNWURzfGQkqxAu17458236 = -7954473;    long foVbYfDlLowpNWURzfGQkqxAu65361014 = -513456026;    long foVbYfDlLowpNWURzfGQkqxAu49971112 = -376066642;    long foVbYfDlLowpNWURzfGQkqxAu64267933 = -405992690;    long foVbYfDlLowpNWURzfGQkqxAu95981819 = -649480950;    long foVbYfDlLowpNWURzfGQkqxAu54123048 = -422418832;    long foVbYfDlLowpNWURzfGQkqxAu52065450 = -864633998;    long foVbYfDlLowpNWURzfGQkqxAu3282452 = -678163050;    long foVbYfDlLowpNWURzfGQkqxAu50395722 = 64125626;    long foVbYfDlLowpNWURzfGQkqxAu67118727 = -744017264;    long foVbYfDlLowpNWURzfGQkqxAu10941888 = -301854394;    long foVbYfDlLowpNWURzfGQkqxAu90214149 = -828428400;    long foVbYfDlLowpNWURzfGQkqxAu22207988 = -367005049;    long foVbYfDlLowpNWURzfGQkqxAu27732720 = -410063190;    long foVbYfDlLowpNWURzfGQkqxAu14413190 = 43341030;    long foVbYfDlLowpNWURzfGQkqxAu50919563 = -354547125;    long foVbYfDlLowpNWURzfGQkqxAu41295638 = -7849845;    long foVbYfDlLowpNWURzfGQkqxAu54258492 = -386171575;    long foVbYfDlLowpNWURzfGQkqxAu97627133 = -328314577;    long foVbYfDlLowpNWURzfGQkqxAu23068753 = -811680268;    long foVbYfDlLowpNWURzfGQkqxAu54716818 = -836318465;    long foVbYfDlLowpNWURzfGQkqxAu26045495 = -329466219;    long foVbYfDlLowpNWURzfGQkqxAu78605681 = -378732723;    long foVbYfDlLowpNWURzfGQkqxAu23152101 = -375621073;    long foVbYfDlLowpNWURzfGQkqxAu84832172 = -704023994;    long foVbYfDlLowpNWURzfGQkqxAu90785011 = -808015073;    long foVbYfDlLowpNWURzfGQkqxAu99353788 = -500849663;    long foVbYfDlLowpNWURzfGQkqxAu46576514 = -964845558;    long foVbYfDlLowpNWURzfGQkqxAu75061049 = -284367221;    long foVbYfDlLowpNWURzfGQkqxAu47729690 = -824857637;    long foVbYfDlLowpNWURzfGQkqxAu94216761 = -565373970;    long foVbYfDlLowpNWURzfGQkqxAu89638676 = -642384979;    long foVbYfDlLowpNWURzfGQkqxAu21373076 = -597266731;    long foVbYfDlLowpNWURzfGQkqxAu86001869 = -596309413;    long foVbYfDlLowpNWURzfGQkqxAu81191870 = -608188971;    long foVbYfDlLowpNWURzfGQkqxAu37130807 = -272720122;    long foVbYfDlLowpNWURzfGQkqxAu80142700 = -566924384;    long foVbYfDlLowpNWURzfGQkqxAu87677047 = -325779174;    long foVbYfDlLowpNWURzfGQkqxAu28129721 = -553912055;    long foVbYfDlLowpNWURzfGQkqxAu43669433 = -19940239;    long foVbYfDlLowpNWURzfGQkqxAu6317828 = -521764112;    long foVbYfDlLowpNWURzfGQkqxAu71713381 = -151183158;    long foVbYfDlLowpNWURzfGQkqxAu98100535 = -877407601;    long foVbYfDlLowpNWURzfGQkqxAu7447766 = -378982713;    long foVbYfDlLowpNWURzfGQkqxAu53878084 = -710575193;    long foVbYfDlLowpNWURzfGQkqxAu59027030 = -617441397;    long foVbYfDlLowpNWURzfGQkqxAu80437388 = 53565617;    long foVbYfDlLowpNWURzfGQkqxAu3262064 = -399282656;    long foVbYfDlLowpNWURzfGQkqxAu31283048 = -691078990;    long foVbYfDlLowpNWURzfGQkqxAu2642232 = -667550960;    long foVbYfDlLowpNWURzfGQkqxAu6125970 = -883032342;    long foVbYfDlLowpNWURzfGQkqxAu38434772 = -35416653;    long foVbYfDlLowpNWURzfGQkqxAu83215604 = -621905893;    long foVbYfDlLowpNWURzfGQkqxAu13489619 = -808315934;    long foVbYfDlLowpNWURzfGQkqxAu6274595 = -805357942;    long foVbYfDlLowpNWURzfGQkqxAu91412741 = -678488254;    long foVbYfDlLowpNWURzfGQkqxAu86755333 = -34723303;    long foVbYfDlLowpNWURzfGQkqxAu26819012 = 99554430;    long foVbYfDlLowpNWURzfGQkqxAu79435760 = -701968696;    long foVbYfDlLowpNWURzfGQkqxAu5196808 = -841465877;    long foVbYfDlLowpNWURzfGQkqxAu54769259 = -921569169;    long foVbYfDlLowpNWURzfGQkqxAu5488936 = -899788441;    long foVbYfDlLowpNWURzfGQkqxAu28221402 = -293795830;    long foVbYfDlLowpNWURzfGQkqxAu2666033 = -111016737;    long foVbYfDlLowpNWURzfGQkqxAu72901965 = -765664672;     foVbYfDlLowpNWURzfGQkqxAu29712651 = foVbYfDlLowpNWURzfGQkqxAu74541751;     foVbYfDlLowpNWURzfGQkqxAu74541751 = foVbYfDlLowpNWURzfGQkqxAu53172174;     foVbYfDlLowpNWURzfGQkqxAu53172174 = foVbYfDlLowpNWURzfGQkqxAu87972072;     foVbYfDlLowpNWURzfGQkqxAu87972072 = foVbYfDlLowpNWURzfGQkqxAu34073352;     foVbYfDlLowpNWURzfGQkqxAu34073352 = foVbYfDlLowpNWURzfGQkqxAu93430388;     foVbYfDlLowpNWURzfGQkqxAu93430388 = foVbYfDlLowpNWURzfGQkqxAu30348572;     foVbYfDlLowpNWURzfGQkqxAu30348572 = foVbYfDlLowpNWURzfGQkqxAu92272751;     foVbYfDlLowpNWURzfGQkqxAu92272751 = foVbYfDlLowpNWURzfGQkqxAu28622844;     foVbYfDlLowpNWURzfGQkqxAu28622844 = foVbYfDlLowpNWURzfGQkqxAu95151296;     foVbYfDlLowpNWURzfGQkqxAu95151296 = foVbYfDlLowpNWURzfGQkqxAu86910024;     foVbYfDlLowpNWURzfGQkqxAu86910024 = foVbYfDlLowpNWURzfGQkqxAu70481413;     foVbYfDlLowpNWURzfGQkqxAu70481413 = foVbYfDlLowpNWURzfGQkqxAu57931447;     foVbYfDlLowpNWURzfGQkqxAu57931447 = foVbYfDlLowpNWURzfGQkqxAu46993282;     foVbYfDlLowpNWURzfGQkqxAu46993282 = foVbYfDlLowpNWURzfGQkqxAu98650106;     foVbYfDlLowpNWURzfGQkqxAu98650106 = foVbYfDlLowpNWURzfGQkqxAu2491821;     foVbYfDlLowpNWURzfGQkqxAu2491821 = foVbYfDlLowpNWURzfGQkqxAu30113813;     foVbYfDlLowpNWURzfGQkqxAu30113813 = foVbYfDlLowpNWURzfGQkqxAu51944980;     foVbYfDlLowpNWURzfGQkqxAu51944980 = foVbYfDlLowpNWURzfGQkqxAu24111540;     foVbYfDlLowpNWURzfGQkqxAu24111540 = foVbYfDlLowpNWURzfGQkqxAu97792481;     foVbYfDlLowpNWURzfGQkqxAu97792481 = foVbYfDlLowpNWURzfGQkqxAu58383278;     foVbYfDlLowpNWURzfGQkqxAu58383278 = foVbYfDlLowpNWURzfGQkqxAu74995832;     foVbYfDlLowpNWURzfGQkqxAu74995832 = foVbYfDlLowpNWURzfGQkqxAu48496257;     foVbYfDlLowpNWURzfGQkqxAu48496257 = foVbYfDlLowpNWURzfGQkqxAu74566493;     foVbYfDlLowpNWURzfGQkqxAu74566493 = foVbYfDlLowpNWURzfGQkqxAu64819972;     foVbYfDlLowpNWURzfGQkqxAu64819972 = foVbYfDlLowpNWURzfGQkqxAu49241179;     foVbYfDlLowpNWURzfGQkqxAu49241179 = foVbYfDlLowpNWURzfGQkqxAu2645377;     foVbYfDlLowpNWURzfGQkqxAu2645377 = foVbYfDlLowpNWURzfGQkqxAu30994783;     foVbYfDlLowpNWURzfGQkqxAu30994783 = foVbYfDlLowpNWURzfGQkqxAu45696237;     foVbYfDlLowpNWURzfGQkqxAu45696237 = foVbYfDlLowpNWURzfGQkqxAu53561795;     foVbYfDlLowpNWURzfGQkqxAu53561795 = foVbYfDlLowpNWURzfGQkqxAu47421607;     foVbYfDlLowpNWURzfGQkqxAu47421607 = foVbYfDlLowpNWURzfGQkqxAu92693263;     foVbYfDlLowpNWURzfGQkqxAu92693263 = foVbYfDlLowpNWURzfGQkqxAu80842737;     foVbYfDlLowpNWURzfGQkqxAu80842737 = foVbYfDlLowpNWURzfGQkqxAu36558372;     foVbYfDlLowpNWURzfGQkqxAu36558372 = foVbYfDlLowpNWURzfGQkqxAu60991412;     foVbYfDlLowpNWURzfGQkqxAu60991412 = foVbYfDlLowpNWURzfGQkqxAu17458236;     foVbYfDlLowpNWURzfGQkqxAu17458236 = foVbYfDlLowpNWURzfGQkqxAu65361014;     foVbYfDlLowpNWURzfGQkqxAu65361014 = foVbYfDlLowpNWURzfGQkqxAu49971112;     foVbYfDlLowpNWURzfGQkqxAu49971112 = foVbYfDlLowpNWURzfGQkqxAu64267933;     foVbYfDlLowpNWURzfGQkqxAu64267933 = foVbYfDlLowpNWURzfGQkqxAu95981819;     foVbYfDlLowpNWURzfGQkqxAu95981819 = foVbYfDlLowpNWURzfGQkqxAu54123048;     foVbYfDlLowpNWURzfGQkqxAu54123048 = foVbYfDlLowpNWURzfGQkqxAu52065450;     foVbYfDlLowpNWURzfGQkqxAu52065450 = foVbYfDlLowpNWURzfGQkqxAu3282452;     foVbYfDlLowpNWURzfGQkqxAu3282452 = foVbYfDlLowpNWURzfGQkqxAu50395722;     foVbYfDlLowpNWURzfGQkqxAu50395722 = foVbYfDlLowpNWURzfGQkqxAu67118727;     foVbYfDlLowpNWURzfGQkqxAu67118727 = foVbYfDlLowpNWURzfGQkqxAu10941888;     foVbYfDlLowpNWURzfGQkqxAu10941888 = foVbYfDlLowpNWURzfGQkqxAu90214149;     foVbYfDlLowpNWURzfGQkqxAu90214149 = foVbYfDlLowpNWURzfGQkqxAu22207988;     foVbYfDlLowpNWURzfGQkqxAu22207988 = foVbYfDlLowpNWURzfGQkqxAu27732720;     foVbYfDlLowpNWURzfGQkqxAu27732720 = foVbYfDlLowpNWURzfGQkqxAu14413190;     foVbYfDlLowpNWURzfGQkqxAu14413190 = foVbYfDlLowpNWURzfGQkqxAu50919563;     foVbYfDlLowpNWURzfGQkqxAu50919563 = foVbYfDlLowpNWURzfGQkqxAu41295638;     foVbYfDlLowpNWURzfGQkqxAu41295638 = foVbYfDlLowpNWURzfGQkqxAu54258492;     foVbYfDlLowpNWURzfGQkqxAu54258492 = foVbYfDlLowpNWURzfGQkqxAu97627133;     foVbYfDlLowpNWURzfGQkqxAu97627133 = foVbYfDlLowpNWURzfGQkqxAu23068753;     foVbYfDlLowpNWURzfGQkqxAu23068753 = foVbYfDlLowpNWURzfGQkqxAu54716818;     foVbYfDlLowpNWURzfGQkqxAu54716818 = foVbYfDlLowpNWURzfGQkqxAu26045495;     foVbYfDlLowpNWURzfGQkqxAu26045495 = foVbYfDlLowpNWURzfGQkqxAu78605681;     foVbYfDlLowpNWURzfGQkqxAu78605681 = foVbYfDlLowpNWURzfGQkqxAu23152101;     foVbYfDlLowpNWURzfGQkqxAu23152101 = foVbYfDlLowpNWURzfGQkqxAu84832172;     foVbYfDlLowpNWURzfGQkqxAu84832172 = foVbYfDlLowpNWURzfGQkqxAu90785011;     foVbYfDlLowpNWURzfGQkqxAu90785011 = foVbYfDlLowpNWURzfGQkqxAu99353788;     foVbYfDlLowpNWURzfGQkqxAu99353788 = foVbYfDlLowpNWURzfGQkqxAu46576514;     foVbYfDlLowpNWURzfGQkqxAu46576514 = foVbYfDlLowpNWURzfGQkqxAu75061049;     foVbYfDlLowpNWURzfGQkqxAu75061049 = foVbYfDlLowpNWURzfGQkqxAu47729690;     foVbYfDlLowpNWURzfGQkqxAu47729690 = foVbYfDlLowpNWURzfGQkqxAu94216761;     foVbYfDlLowpNWURzfGQkqxAu94216761 = foVbYfDlLowpNWURzfGQkqxAu89638676;     foVbYfDlLowpNWURzfGQkqxAu89638676 = foVbYfDlLowpNWURzfGQkqxAu21373076;     foVbYfDlLowpNWURzfGQkqxAu21373076 = foVbYfDlLowpNWURzfGQkqxAu86001869;     foVbYfDlLowpNWURzfGQkqxAu86001869 = foVbYfDlLowpNWURzfGQkqxAu81191870;     foVbYfDlLowpNWURzfGQkqxAu81191870 = foVbYfDlLowpNWURzfGQkqxAu37130807;     foVbYfDlLowpNWURzfGQkqxAu37130807 = foVbYfDlLowpNWURzfGQkqxAu80142700;     foVbYfDlLowpNWURzfGQkqxAu80142700 = foVbYfDlLowpNWURzfGQkqxAu87677047;     foVbYfDlLowpNWURzfGQkqxAu87677047 = foVbYfDlLowpNWURzfGQkqxAu28129721;     foVbYfDlLowpNWURzfGQkqxAu28129721 = foVbYfDlLowpNWURzfGQkqxAu43669433;     foVbYfDlLowpNWURzfGQkqxAu43669433 = foVbYfDlLowpNWURzfGQkqxAu6317828;     foVbYfDlLowpNWURzfGQkqxAu6317828 = foVbYfDlLowpNWURzfGQkqxAu71713381;     foVbYfDlLowpNWURzfGQkqxAu71713381 = foVbYfDlLowpNWURzfGQkqxAu98100535;     foVbYfDlLowpNWURzfGQkqxAu98100535 = foVbYfDlLowpNWURzfGQkqxAu7447766;     foVbYfDlLowpNWURzfGQkqxAu7447766 = foVbYfDlLowpNWURzfGQkqxAu53878084;     foVbYfDlLowpNWURzfGQkqxAu53878084 = foVbYfDlLowpNWURzfGQkqxAu59027030;     foVbYfDlLowpNWURzfGQkqxAu59027030 = foVbYfDlLowpNWURzfGQkqxAu80437388;     foVbYfDlLowpNWURzfGQkqxAu80437388 = foVbYfDlLowpNWURzfGQkqxAu3262064;     foVbYfDlLowpNWURzfGQkqxAu3262064 = foVbYfDlLowpNWURzfGQkqxAu31283048;     foVbYfDlLowpNWURzfGQkqxAu31283048 = foVbYfDlLowpNWURzfGQkqxAu2642232;     foVbYfDlLowpNWURzfGQkqxAu2642232 = foVbYfDlLowpNWURzfGQkqxAu6125970;     foVbYfDlLowpNWURzfGQkqxAu6125970 = foVbYfDlLowpNWURzfGQkqxAu38434772;     foVbYfDlLowpNWURzfGQkqxAu38434772 = foVbYfDlLowpNWURzfGQkqxAu83215604;     foVbYfDlLowpNWURzfGQkqxAu83215604 = foVbYfDlLowpNWURzfGQkqxAu13489619;     foVbYfDlLowpNWURzfGQkqxAu13489619 = foVbYfDlLowpNWURzfGQkqxAu6274595;     foVbYfDlLowpNWURzfGQkqxAu6274595 = foVbYfDlLowpNWURzfGQkqxAu91412741;     foVbYfDlLowpNWURzfGQkqxAu91412741 = foVbYfDlLowpNWURzfGQkqxAu86755333;     foVbYfDlLowpNWURzfGQkqxAu86755333 = foVbYfDlLowpNWURzfGQkqxAu26819012;     foVbYfDlLowpNWURzfGQkqxAu26819012 = foVbYfDlLowpNWURzfGQkqxAu79435760;     foVbYfDlLowpNWURzfGQkqxAu79435760 = foVbYfDlLowpNWURzfGQkqxAu5196808;     foVbYfDlLowpNWURzfGQkqxAu5196808 = foVbYfDlLowpNWURzfGQkqxAu54769259;     foVbYfDlLowpNWURzfGQkqxAu54769259 = foVbYfDlLowpNWURzfGQkqxAu5488936;     foVbYfDlLowpNWURzfGQkqxAu5488936 = foVbYfDlLowpNWURzfGQkqxAu28221402;     foVbYfDlLowpNWURzfGQkqxAu28221402 = foVbYfDlLowpNWURzfGQkqxAu2666033;     foVbYfDlLowpNWURzfGQkqxAu2666033 = foVbYfDlLowpNWURzfGQkqxAu72901965;     foVbYfDlLowpNWURzfGQkqxAu72901965 = foVbYfDlLowpNWURzfGQkqxAu29712651;}
// Junk Finished
