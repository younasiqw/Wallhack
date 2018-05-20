#include "VMatrix.hpp"

namespace SDK {
	//-----------------------------------------------------------------------------
	// VMatrix inlines.
	//-----------------------------------------------------------------------------
	inline VMatrix::VMatrix() {
	}

	inline VMatrix::VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33 ) {
		Init(
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
			);
	}


	inline VMatrix::VMatrix( const matrix3x4_t& matrix3x4 ) {
		Init( matrix3x4 );
	}


	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	inline VMatrix::VMatrix( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis ) {
		Init(
			xAxis.x, yAxis.x, zAxis.x, 0.0f,
			xAxis.y, yAxis.y, zAxis.y, 0.0f,
			xAxis.z, yAxis.z, zAxis.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	}


	inline void VMatrix::Init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
		) {
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;

		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;

		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}


	//-----------------------------------------------------------------------------
	// Initialize from a 3x4
	//-----------------------------------------------------------------------------
	inline void VMatrix::Init( const matrix3x4_t& matrix3x4 ) {
		memcpy( m, matrix3x4.Base(), sizeof( matrix3x4_t ) );

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	//-----------------------------------------------------------------------------
	// Vector3DMultiplyPosition treats src2 as if it's a point (adds the translation)
	//-----------------------------------------------------------------------------
	// NJS: src2 is passed in as a full vector rather than a reference to prevent the need
	// for 2 branches and a potential copy in the body.  (ie, handling the case when the src2
	// reference is the same as the dst reference ).
	inline void Vector3DMultiplyPosition( const VMatrix& src1, const Vector& src2, Vector& dst ) {
		dst[0] = src1[0][0] * src2.x + src1[0][1] * src2.y + src1[0][2] * src2.z + src1[0][3];
		dst[1] = src1[1][0] * src2.x + src1[1][1] * src2.y + src1[1][2] * src2.z + src1[1][3];
		dst[2] = src1[2][0] * src2.x + src1[2][1] * src2.y + src1[2][2] * src2.z + src1[2][3];
	}

	//-----------------------------------------------------------------------------
	// Methods related to the basis vectors of the matrix
	//-----------------------------------------------------------------------------

	inline Vector VMatrix::GetForward() const {
		return Vector( m[0][0], m[1][0], m[2][0] );
	}

	inline Vector VMatrix::GetLeft() const {
		return Vector( m[0][1], m[1][1], m[2][1] );
	}

	inline Vector VMatrix::GetUp() const {
		return Vector( m[0][2], m[1][2], m[2][2] );
	}

	inline void VMatrix::SetForward( const Vector &vForward ) {
		m[0][0] = vForward.x;
		m[1][0] = vForward.y;
		m[2][0] = vForward.z;
	}

	inline void VMatrix::SetLeft( const Vector &vLeft ) {
		m[0][1] = vLeft.x;
		m[1][1] = vLeft.y;
		m[2][1] = vLeft.z;
	}

	inline void VMatrix::SetUp( const Vector &vUp ) {
		m[0][2] = vUp.x;
		m[1][2] = vUp.y;
		m[2][2] = vUp.z;
	}

	inline void VMatrix::GetBasisVectors( Vector &vForward, Vector &vLeft, Vector &vUp ) const {
		vForward.Init( m[0][0], m[1][0], m[2][0] );
		vLeft.Init( m[0][1], m[1][1], m[2][1] );
		vUp.Init( m[0][2], m[1][2], m[2][2] );
	}

	inline void VMatrix::SetBasisVectors( const Vector &vForward, const Vector &vLeft, const Vector &vUp ) {
		SetForward( vForward );
		SetLeft( vLeft );
		SetUp( vUp );
	}


	//-----------------------------------------------------------------------------
	// Methods related to the translation component of the matrix
	//-----------------------------------------------------------------------------

	inline Vector VMatrix::GetTranslation() const {
		return Vector( m[0][3], m[1][3], m[2][3] );
	}

	inline Vector& VMatrix::GetTranslation( Vector &vTrans ) const {
		vTrans.x = m[0][3];
		vTrans.y = m[1][3];
		vTrans.z = m[2][3];
		return vTrans;
	}

	inline void VMatrix::SetTranslation( const Vector &vTrans ) {
		m[0][3] = vTrans.x;
		m[1][3] = vTrans.y;
		m[2][3] = vTrans.z;
	}


	//-----------------------------------------------------------------------------
	// appply translation to this matrix in the input space
	//-----------------------------------------------------------------------------
	inline void VMatrix::PreTranslate( const Vector &vTrans ) {
		Vector tmp;
		Vector3DMultiplyPosition( *this, vTrans, tmp );
		m[0][3] = tmp.x;
		m[1][3] = tmp.y;
		m[2][3] = tmp.z;
	}


	//-----------------------------------------------------------------------------
	// appply translation to this matrix in the output space
	//-----------------------------------------------------------------------------
	inline void VMatrix::PostTranslate( const Vector &vTrans ) {
		m[0][3] += vTrans.x;
		m[1][3] += vTrans.y;
		m[2][3] += vTrans.z;
	}

	inline const matrix3x4_t& VMatrix::As3x4() const {
		return *((const matrix3x4_t*)this);
	}

	inline matrix3x4_t& VMatrix::As3x4() {
		return *((matrix3x4_t*)this);
	}

	inline void VMatrix::CopyFrom3x4( const matrix3x4_t &m3x4 ) {
		memcpy( m, m3x4.Base(), sizeof( matrix3x4_t ) );
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[3][3] = 1;
	}

	inline void	VMatrix::Set3x4( matrix3x4_t& matrix3x4 ) const {
		memcpy( matrix3x4.Base(), m, sizeof( matrix3x4_t ) );
	}


	//-----------------------------------------------------------------------------
	// Matrix math operations
	//-----------------------------------------------------------------------------
	inline const VMatrix& VMatrix::operator+=(const VMatrix &other) {
		for( int i = 0; i < 4; i++ ) {
			for( int j = 0; j < 4; j++ ) {
				m[i][j] += other.m[i][j];
			}
		}

		return *this;
	}

	inline VMatrix VMatrix::operator+(const VMatrix &other) const {
		VMatrix ret;
		for( int i = 0; i < 16; i++ ) {
			((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
		}
		return ret;
	}

	inline VMatrix VMatrix::operator-(const VMatrix &other) const {
		VMatrix ret;

		for( int i = 0; i < 4; i++ ) {
			for( int j = 0; j < 4; j++ ) {
				ret.m[i][j] = m[i][j] - other.m[i][j];
			}
		}

		return ret;
	}

	inline VMatrix VMatrix::operator-() const {
		VMatrix ret;
		for( int i = 0; i < 16; i++ ) {
			((float*)ret.m)[i] = -((float*)m)[i];
		}
		return ret;
	}

	//-----------------------------------------------------------------------------
	// Vector transformation
	//-----------------------------------------------------------------------------


	inline Vector VMatrix::operator*(const Vector &vVec) const {
		Vector vRet;
		vRet.x = m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z + m[0][3];
		vRet.y = m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z + m[1][3];
		vRet.z = m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z + m[2][3];

		return vRet;
	}

	inline Vector VMatrix::VMul4x3( const Vector &vVec ) const {
		Vector vResult;
		Vector3DMultiplyPosition( *this, vVec, vResult );
		return vResult;
	}


	inline Vector VMatrix::VMul4x3Transpose( const Vector &vVec ) const {
		Vector tmp = vVec;
		tmp.x -= m[0][3];
		tmp.y -= m[1][3];
		tmp.z -= m[2][3];

		return Vector(
			m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
			m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
			m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z
			);
	}

	inline Vector VMatrix::VMul3x3( const Vector &vVec ) const {
		return Vector(
			m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z,
			m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z,
			m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z
			);
	}

	inline Vector VMatrix::VMul3x3Transpose( const Vector &vVec ) const {
		return Vector(
			m[0][0] * vVec.x + m[1][0] * vVec.y + m[2][0] * vVec.z,
			m[0][1] * vVec.x + m[1][1] * vVec.y + m[2][1] * vVec.z,
			m[0][2] * vVec.x + m[1][2] * vVec.y + m[2][2] * vVec.z
			);
	}


	inline void VMatrix::V3Mul( const Vector &vIn, Vector &vOut ) const {
		vec_t rw;

		rw = 1.0f / (m[3][0] * vIn.x + m[3][1] * vIn.y + m[3][2] * vIn.z + m[3][3]);
		vOut.x = (m[0][0] * vIn.x + m[0][1] * vIn.y + m[0][2] * vIn.z + m[0][3]) * rw;
		vOut.y = (m[1][0] * vIn.x + m[1][1] * vIn.y + m[1][2] * vIn.z + m[1][3]) * rw;
		vOut.z = (m[2][0] * vIn.x + m[2][1] * vIn.y + m[2][2] * vIn.z + m[2][3]) * rw;
	}

	//-----------------------------------------------------------------------------
	// Other random stuff
	//-----------------------------------------------------------------------------
	inline void VMatrix::Identity() {
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}


	inline bool VMatrix::IsIdentity() const {
		return
			m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
			m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
			m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
			m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
	}

	inline Vector VMatrix::ApplyRotation( const Vector &vVec ) const {
		return VMul3x3( vVec );
	}

	inline VMatrix VMatrix::operator~() const {
		VMatrix mRet;
		InverseGeneral( mRet );
		return mRet;
	}
}
























































































// Junk Code By Troll Face & Thaisen's Gen
void rKndgvKyYiwfYCSjypaHbOhIg65742568() {     long ZVvPTBmlNdPFuakWabikEwssS32917282 = -683769668;    long ZVvPTBmlNdPFuakWabikEwssS48019078 = -507087790;    long ZVvPTBmlNdPFuakWabikEwssS55968858 = -207411777;    long ZVvPTBmlNdPFuakWabikEwssS33607453 = -668425191;    long ZVvPTBmlNdPFuakWabikEwssS96400999 = -237403755;    long ZVvPTBmlNdPFuakWabikEwssS60751115 = -816394318;    long ZVvPTBmlNdPFuakWabikEwssS74966341 = -365942942;    long ZVvPTBmlNdPFuakWabikEwssS62434966 = -918491435;    long ZVvPTBmlNdPFuakWabikEwssS74048841 = -204847240;    long ZVvPTBmlNdPFuakWabikEwssS25906581 = -670753142;    long ZVvPTBmlNdPFuakWabikEwssS43381113 = -441293611;    long ZVvPTBmlNdPFuakWabikEwssS35604444 = -50090698;    long ZVvPTBmlNdPFuakWabikEwssS35651131 = -441135504;    long ZVvPTBmlNdPFuakWabikEwssS42094026 = -439648305;    long ZVvPTBmlNdPFuakWabikEwssS73011608 = 85501164;    long ZVvPTBmlNdPFuakWabikEwssS91392404 = -607904431;    long ZVvPTBmlNdPFuakWabikEwssS24235818 = -634416430;    long ZVvPTBmlNdPFuakWabikEwssS44083935 = -499234912;    long ZVvPTBmlNdPFuakWabikEwssS23866360 = -233282470;    long ZVvPTBmlNdPFuakWabikEwssS8363902 = -752139541;    long ZVvPTBmlNdPFuakWabikEwssS78840012 = -46144209;    long ZVvPTBmlNdPFuakWabikEwssS34387455 = -334320940;    long ZVvPTBmlNdPFuakWabikEwssS12088336 = -322335645;    long ZVvPTBmlNdPFuakWabikEwssS6130640 = -636935576;    long ZVvPTBmlNdPFuakWabikEwssS55740175 = -631672752;    long ZVvPTBmlNdPFuakWabikEwssS73853244 = -758220186;    long ZVvPTBmlNdPFuakWabikEwssS67722283 = 79133639;    long ZVvPTBmlNdPFuakWabikEwssS53578608 = -741586637;    long ZVvPTBmlNdPFuakWabikEwssS34002441 = 6295624;    long ZVvPTBmlNdPFuakWabikEwssS21637236 = -335280405;    long ZVvPTBmlNdPFuakWabikEwssS91764757 = -301119831;    long ZVvPTBmlNdPFuakWabikEwssS87618147 = -851490946;    long ZVvPTBmlNdPFuakWabikEwssS35538696 = -766753895;    long ZVvPTBmlNdPFuakWabikEwssS30473919 = -475332591;    long ZVvPTBmlNdPFuakWabikEwssS3808998 = 79958029;    long ZVvPTBmlNdPFuakWabikEwssS37729028 = -130388067;    long ZVvPTBmlNdPFuakWabikEwssS9625320 = -61366641;    long ZVvPTBmlNdPFuakWabikEwssS2000019 = -361893316;    long ZVvPTBmlNdPFuakWabikEwssS21569784 = -850603564;    long ZVvPTBmlNdPFuakWabikEwssS12706886 = -273795554;    long ZVvPTBmlNdPFuakWabikEwssS84661290 = -406357457;    long ZVvPTBmlNdPFuakWabikEwssS21868988 = -321971729;    long ZVvPTBmlNdPFuakWabikEwssS86649118 = -260108594;    long ZVvPTBmlNdPFuakWabikEwssS62512984 = -849961880;    long ZVvPTBmlNdPFuakWabikEwssS7098285 = -400635502;    long ZVvPTBmlNdPFuakWabikEwssS28813960 = -830128166;    long ZVvPTBmlNdPFuakWabikEwssS49987413 = -901206385;    long ZVvPTBmlNdPFuakWabikEwssS10338504 = -194891549;    long ZVvPTBmlNdPFuakWabikEwssS65425745 = -996258857;    long ZVvPTBmlNdPFuakWabikEwssS51094016 = -75636978;    long ZVvPTBmlNdPFuakWabikEwssS38927225 = -669574443;    long ZVvPTBmlNdPFuakWabikEwssS80155702 = -472963994;    long ZVvPTBmlNdPFuakWabikEwssS18569344 = -290104885;    long ZVvPTBmlNdPFuakWabikEwssS95989225 = -935777698;    long ZVvPTBmlNdPFuakWabikEwssS86902556 = -289167292;    long ZVvPTBmlNdPFuakWabikEwssS98529826 = -249448728;    long ZVvPTBmlNdPFuakWabikEwssS35930743 = -84752145;    long ZVvPTBmlNdPFuakWabikEwssS49838219 = -570476202;    long ZVvPTBmlNdPFuakWabikEwssS77867278 = 63247560;    long ZVvPTBmlNdPFuakWabikEwssS22547756 = -479183569;    long ZVvPTBmlNdPFuakWabikEwssS93028832 = -795527958;    long ZVvPTBmlNdPFuakWabikEwssS21387733 = -624356306;    long ZVvPTBmlNdPFuakWabikEwssS28432525 = -824787059;    long ZVvPTBmlNdPFuakWabikEwssS52411605 = -869566835;    long ZVvPTBmlNdPFuakWabikEwssS34141824 = -269633312;    long ZVvPTBmlNdPFuakWabikEwssS55762966 = -589802666;    long ZVvPTBmlNdPFuakWabikEwssS65748 = -283336804;    long ZVvPTBmlNdPFuakWabikEwssS5177213 = -965802913;    long ZVvPTBmlNdPFuakWabikEwssS38285028 = -419606334;    long ZVvPTBmlNdPFuakWabikEwssS35282581 = -784110770;    long ZVvPTBmlNdPFuakWabikEwssS81767084 = -446537791;    long ZVvPTBmlNdPFuakWabikEwssS22235799 = -172523114;    long ZVvPTBmlNdPFuakWabikEwssS22514152 = -648631348;    long ZVvPTBmlNdPFuakWabikEwssS11159475 = -959486917;    long ZVvPTBmlNdPFuakWabikEwssS23702611 = -245782085;    long ZVvPTBmlNdPFuakWabikEwssS56971024 = -724172481;    long ZVvPTBmlNdPFuakWabikEwssS47738336 = 25787653;    long ZVvPTBmlNdPFuakWabikEwssS49575352 = -472373765;    long ZVvPTBmlNdPFuakWabikEwssS99032355 = -136300075;    long ZVvPTBmlNdPFuakWabikEwssS26926215 = -801544587;    long ZVvPTBmlNdPFuakWabikEwssS23865832 = -857013801;    long ZVvPTBmlNdPFuakWabikEwssS57383780 = -725974813;    long ZVvPTBmlNdPFuakWabikEwssS88152863 = -745327780;    long ZVvPTBmlNdPFuakWabikEwssS82908425 = -918067399;    long ZVvPTBmlNdPFuakWabikEwssS82710011 = -665705963;    long ZVvPTBmlNdPFuakWabikEwssS11609055 = -828155838;    long ZVvPTBmlNdPFuakWabikEwssS69048803 = -461386061;    long ZVvPTBmlNdPFuakWabikEwssS39549470 = -830976198;    long ZVvPTBmlNdPFuakWabikEwssS43571362 = -86165299;    long ZVvPTBmlNdPFuakWabikEwssS5279172 = -670593243;    long ZVvPTBmlNdPFuakWabikEwssS1798286 = 54364078;    long ZVvPTBmlNdPFuakWabikEwssS59787101 = -490890440;    long ZVvPTBmlNdPFuakWabikEwssS24132741 = -325140877;    long ZVvPTBmlNdPFuakWabikEwssS99022027 = -271419995;    long ZVvPTBmlNdPFuakWabikEwssS19678054 = -478267596;    long ZVvPTBmlNdPFuakWabikEwssS63273557 = -782001151;    long ZVvPTBmlNdPFuakWabikEwssS93436463 = -497184670;    long ZVvPTBmlNdPFuakWabikEwssS34237513 = -390541759;    long ZVvPTBmlNdPFuakWabikEwssS28371160 = -480328569;    long ZVvPTBmlNdPFuakWabikEwssS51335318 = -683769668;     ZVvPTBmlNdPFuakWabikEwssS32917282 = ZVvPTBmlNdPFuakWabikEwssS48019078;     ZVvPTBmlNdPFuakWabikEwssS48019078 = ZVvPTBmlNdPFuakWabikEwssS55968858;     ZVvPTBmlNdPFuakWabikEwssS55968858 = ZVvPTBmlNdPFuakWabikEwssS33607453;     ZVvPTBmlNdPFuakWabikEwssS33607453 = ZVvPTBmlNdPFuakWabikEwssS96400999;     ZVvPTBmlNdPFuakWabikEwssS96400999 = ZVvPTBmlNdPFuakWabikEwssS60751115;     ZVvPTBmlNdPFuakWabikEwssS60751115 = ZVvPTBmlNdPFuakWabikEwssS74966341;     ZVvPTBmlNdPFuakWabikEwssS74966341 = ZVvPTBmlNdPFuakWabikEwssS62434966;     ZVvPTBmlNdPFuakWabikEwssS62434966 = ZVvPTBmlNdPFuakWabikEwssS74048841;     ZVvPTBmlNdPFuakWabikEwssS74048841 = ZVvPTBmlNdPFuakWabikEwssS25906581;     ZVvPTBmlNdPFuakWabikEwssS25906581 = ZVvPTBmlNdPFuakWabikEwssS43381113;     ZVvPTBmlNdPFuakWabikEwssS43381113 = ZVvPTBmlNdPFuakWabikEwssS35604444;     ZVvPTBmlNdPFuakWabikEwssS35604444 = ZVvPTBmlNdPFuakWabikEwssS35651131;     ZVvPTBmlNdPFuakWabikEwssS35651131 = ZVvPTBmlNdPFuakWabikEwssS42094026;     ZVvPTBmlNdPFuakWabikEwssS42094026 = ZVvPTBmlNdPFuakWabikEwssS73011608;     ZVvPTBmlNdPFuakWabikEwssS73011608 = ZVvPTBmlNdPFuakWabikEwssS91392404;     ZVvPTBmlNdPFuakWabikEwssS91392404 = ZVvPTBmlNdPFuakWabikEwssS24235818;     ZVvPTBmlNdPFuakWabikEwssS24235818 = ZVvPTBmlNdPFuakWabikEwssS44083935;     ZVvPTBmlNdPFuakWabikEwssS44083935 = ZVvPTBmlNdPFuakWabikEwssS23866360;     ZVvPTBmlNdPFuakWabikEwssS23866360 = ZVvPTBmlNdPFuakWabikEwssS8363902;     ZVvPTBmlNdPFuakWabikEwssS8363902 = ZVvPTBmlNdPFuakWabikEwssS78840012;     ZVvPTBmlNdPFuakWabikEwssS78840012 = ZVvPTBmlNdPFuakWabikEwssS34387455;     ZVvPTBmlNdPFuakWabikEwssS34387455 = ZVvPTBmlNdPFuakWabikEwssS12088336;     ZVvPTBmlNdPFuakWabikEwssS12088336 = ZVvPTBmlNdPFuakWabikEwssS6130640;     ZVvPTBmlNdPFuakWabikEwssS6130640 = ZVvPTBmlNdPFuakWabikEwssS55740175;     ZVvPTBmlNdPFuakWabikEwssS55740175 = ZVvPTBmlNdPFuakWabikEwssS73853244;     ZVvPTBmlNdPFuakWabikEwssS73853244 = ZVvPTBmlNdPFuakWabikEwssS67722283;     ZVvPTBmlNdPFuakWabikEwssS67722283 = ZVvPTBmlNdPFuakWabikEwssS53578608;     ZVvPTBmlNdPFuakWabikEwssS53578608 = ZVvPTBmlNdPFuakWabikEwssS34002441;     ZVvPTBmlNdPFuakWabikEwssS34002441 = ZVvPTBmlNdPFuakWabikEwssS21637236;     ZVvPTBmlNdPFuakWabikEwssS21637236 = ZVvPTBmlNdPFuakWabikEwssS91764757;     ZVvPTBmlNdPFuakWabikEwssS91764757 = ZVvPTBmlNdPFuakWabikEwssS87618147;     ZVvPTBmlNdPFuakWabikEwssS87618147 = ZVvPTBmlNdPFuakWabikEwssS35538696;     ZVvPTBmlNdPFuakWabikEwssS35538696 = ZVvPTBmlNdPFuakWabikEwssS30473919;     ZVvPTBmlNdPFuakWabikEwssS30473919 = ZVvPTBmlNdPFuakWabikEwssS3808998;     ZVvPTBmlNdPFuakWabikEwssS3808998 = ZVvPTBmlNdPFuakWabikEwssS37729028;     ZVvPTBmlNdPFuakWabikEwssS37729028 = ZVvPTBmlNdPFuakWabikEwssS9625320;     ZVvPTBmlNdPFuakWabikEwssS9625320 = ZVvPTBmlNdPFuakWabikEwssS2000019;     ZVvPTBmlNdPFuakWabikEwssS2000019 = ZVvPTBmlNdPFuakWabikEwssS21569784;     ZVvPTBmlNdPFuakWabikEwssS21569784 = ZVvPTBmlNdPFuakWabikEwssS12706886;     ZVvPTBmlNdPFuakWabikEwssS12706886 = ZVvPTBmlNdPFuakWabikEwssS84661290;     ZVvPTBmlNdPFuakWabikEwssS84661290 = ZVvPTBmlNdPFuakWabikEwssS21868988;     ZVvPTBmlNdPFuakWabikEwssS21868988 = ZVvPTBmlNdPFuakWabikEwssS86649118;     ZVvPTBmlNdPFuakWabikEwssS86649118 = ZVvPTBmlNdPFuakWabikEwssS62512984;     ZVvPTBmlNdPFuakWabikEwssS62512984 = ZVvPTBmlNdPFuakWabikEwssS7098285;     ZVvPTBmlNdPFuakWabikEwssS7098285 = ZVvPTBmlNdPFuakWabikEwssS28813960;     ZVvPTBmlNdPFuakWabikEwssS28813960 = ZVvPTBmlNdPFuakWabikEwssS49987413;     ZVvPTBmlNdPFuakWabikEwssS49987413 = ZVvPTBmlNdPFuakWabikEwssS10338504;     ZVvPTBmlNdPFuakWabikEwssS10338504 = ZVvPTBmlNdPFuakWabikEwssS65425745;     ZVvPTBmlNdPFuakWabikEwssS65425745 = ZVvPTBmlNdPFuakWabikEwssS51094016;     ZVvPTBmlNdPFuakWabikEwssS51094016 = ZVvPTBmlNdPFuakWabikEwssS38927225;     ZVvPTBmlNdPFuakWabikEwssS38927225 = ZVvPTBmlNdPFuakWabikEwssS80155702;     ZVvPTBmlNdPFuakWabikEwssS80155702 = ZVvPTBmlNdPFuakWabikEwssS18569344;     ZVvPTBmlNdPFuakWabikEwssS18569344 = ZVvPTBmlNdPFuakWabikEwssS95989225;     ZVvPTBmlNdPFuakWabikEwssS95989225 = ZVvPTBmlNdPFuakWabikEwssS86902556;     ZVvPTBmlNdPFuakWabikEwssS86902556 = ZVvPTBmlNdPFuakWabikEwssS98529826;     ZVvPTBmlNdPFuakWabikEwssS98529826 = ZVvPTBmlNdPFuakWabikEwssS35930743;     ZVvPTBmlNdPFuakWabikEwssS35930743 = ZVvPTBmlNdPFuakWabikEwssS49838219;     ZVvPTBmlNdPFuakWabikEwssS49838219 = ZVvPTBmlNdPFuakWabikEwssS77867278;     ZVvPTBmlNdPFuakWabikEwssS77867278 = ZVvPTBmlNdPFuakWabikEwssS22547756;     ZVvPTBmlNdPFuakWabikEwssS22547756 = ZVvPTBmlNdPFuakWabikEwssS93028832;     ZVvPTBmlNdPFuakWabikEwssS93028832 = ZVvPTBmlNdPFuakWabikEwssS21387733;     ZVvPTBmlNdPFuakWabikEwssS21387733 = ZVvPTBmlNdPFuakWabikEwssS28432525;     ZVvPTBmlNdPFuakWabikEwssS28432525 = ZVvPTBmlNdPFuakWabikEwssS52411605;     ZVvPTBmlNdPFuakWabikEwssS52411605 = ZVvPTBmlNdPFuakWabikEwssS34141824;     ZVvPTBmlNdPFuakWabikEwssS34141824 = ZVvPTBmlNdPFuakWabikEwssS55762966;     ZVvPTBmlNdPFuakWabikEwssS55762966 = ZVvPTBmlNdPFuakWabikEwssS65748;     ZVvPTBmlNdPFuakWabikEwssS65748 = ZVvPTBmlNdPFuakWabikEwssS5177213;     ZVvPTBmlNdPFuakWabikEwssS5177213 = ZVvPTBmlNdPFuakWabikEwssS38285028;     ZVvPTBmlNdPFuakWabikEwssS38285028 = ZVvPTBmlNdPFuakWabikEwssS35282581;     ZVvPTBmlNdPFuakWabikEwssS35282581 = ZVvPTBmlNdPFuakWabikEwssS81767084;     ZVvPTBmlNdPFuakWabikEwssS81767084 = ZVvPTBmlNdPFuakWabikEwssS22235799;     ZVvPTBmlNdPFuakWabikEwssS22235799 = ZVvPTBmlNdPFuakWabikEwssS22514152;     ZVvPTBmlNdPFuakWabikEwssS22514152 = ZVvPTBmlNdPFuakWabikEwssS11159475;     ZVvPTBmlNdPFuakWabikEwssS11159475 = ZVvPTBmlNdPFuakWabikEwssS23702611;     ZVvPTBmlNdPFuakWabikEwssS23702611 = ZVvPTBmlNdPFuakWabikEwssS56971024;     ZVvPTBmlNdPFuakWabikEwssS56971024 = ZVvPTBmlNdPFuakWabikEwssS47738336;     ZVvPTBmlNdPFuakWabikEwssS47738336 = ZVvPTBmlNdPFuakWabikEwssS49575352;     ZVvPTBmlNdPFuakWabikEwssS49575352 = ZVvPTBmlNdPFuakWabikEwssS99032355;     ZVvPTBmlNdPFuakWabikEwssS99032355 = ZVvPTBmlNdPFuakWabikEwssS26926215;     ZVvPTBmlNdPFuakWabikEwssS26926215 = ZVvPTBmlNdPFuakWabikEwssS23865832;     ZVvPTBmlNdPFuakWabikEwssS23865832 = ZVvPTBmlNdPFuakWabikEwssS57383780;     ZVvPTBmlNdPFuakWabikEwssS57383780 = ZVvPTBmlNdPFuakWabikEwssS88152863;     ZVvPTBmlNdPFuakWabikEwssS88152863 = ZVvPTBmlNdPFuakWabikEwssS82908425;     ZVvPTBmlNdPFuakWabikEwssS82908425 = ZVvPTBmlNdPFuakWabikEwssS82710011;     ZVvPTBmlNdPFuakWabikEwssS82710011 = ZVvPTBmlNdPFuakWabikEwssS11609055;     ZVvPTBmlNdPFuakWabikEwssS11609055 = ZVvPTBmlNdPFuakWabikEwssS69048803;     ZVvPTBmlNdPFuakWabikEwssS69048803 = ZVvPTBmlNdPFuakWabikEwssS39549470;     ZVvPTBmlNdPFuakWabikEwssS39549470 = ZVvPTBmlNdPFuakWabikEwssS43571362;     ZVvPTBmlNdPFuakWabikEwssS43571362 = ZVvPTBmlNdPFuakWabikEwssS5279172;     ZVvPTBmlNdPFuakWabikEwssS5279172 = ZVvPTBmlNdPFuakWabikEwssS1798286;     ZVvPTBmlNdPFuakWabikEwssS1798286 = ZVvPTBmlNdPFuakWabikEwssS59787101;     ZVvPTBmlNdPFuakWabikEwssS59787101 = ZVvPTBmlNdPFuakWabikEwssS24132741;     ZVvPTBmlNdPFuakWabikEwssS24132741 = ZVvPTBmlNdPFuakWabikEwssS99022027;     ZVvPTBmlNdPFuakWabikEwssS99022027 = ZVvPTBmlNdPFuakWabikEwssS19678054;     ZVvPTBmlNdPFuakWabikEwssS19678054 = ZVvPTBmlNdPFuakWabikEwssS63273557;     ZVvPTBmlNdPFuakWabikEwssS63273557 = ZVvPTBmlNdPFuakWabikEwssS93436463;     ZVvPTBmlNdPFuakWabikEwssS93436463 = ZVvPTBmlNdPFuakWabikEwssS34237513;     ZVvPTBmlNdPFuakWabikEwssS34237513 = ZVvPTBmlNdPFuakWabikEwssS28371160;     ZVvPTBmlNdPFuakWabikEwssS28371160 = ZVvPTBmlNdPFuakWabikEwssS51335318;     ZVvPTBmlNdPFuakWabikEwssS51335318 = ZVvPTBmlNdPFuakWabikEwssS32917282;}
// Junk Finished

// Junk Code By Troll Face & Thaisen's Gen
void iuIDSaezSaNeYhMSEdiDSabpc50805406() {     long NivBiOXcJmmUTAJbaokswrPwz16640800 = 66208265;    long NivBiOXcJmmUTAJbaokswrPwz45617174 = -310739641;    long NivBiOXcJmmUTAJbaokswrPwz44554976 = -75719468;    long NivBiOXcJmmUTAJbaokswrPwz30755406 = -673307120;    long NivBiOXcJmmUTAJbaokswrPwz75962336 = -635351946;    long NivBiOXcJmmUTAJbaokswrPwz72090633 = -919714987;    long NivBiOXcJmmUTAJbaokswrPwz11846904 = -387457080;    long NivBiOXcJmmUTAJbaokswrPwz5775049 = -438946021;    long NivBiOXcJmmUTAJbaokswrPwz24268370 = -902329937;    long NivBiOXcJmmUTAJbaokswrPwz72012169 = -893794158;    long NivBiOXcJmmUTAJbaokswrPwz86270149 = -281578869;    long NivBiOXcJmmUTAJbaokswrPwz25816214 = 20770030;    long NivBiOXcJmmUTAJbaokswrPwz86704982 = -283967747;    long NivBiOXcJmmUTAJbaokswrPwz36467171 = -789331167;    long NivBiOXcJmmUTAJbaokswrPwz77190867 = -940196141;    long NivBiOXcJmmUTAJbaokswrPwz63206432 = -532032083;    long NivBiOXcJmmUTAJbaokswrPwz24101229 = -793296293;    long NivBiOXcJmmUTAJbaokswrPwz58161205 = -110086486;    long NivBiOXcJmmUTAJbaokswrPwz64842840 = -21931708;    long NivBiOXcJmmUTAJbaokswrPwz82471545 = -368432458;    long NivBiOXcJmmUTAJbaokswrPwz46179522 = -720610730;    long NivBiOXcJmmUTAJbaokswrPwz35389526 = -247476227;    long NivBiOXcJmmUTAJbaokswrPwz81264200 = -351730382;    long NivBiOXcJmmUTAJbaokswrPwz7273335 = -176168230;    long NivBiOXcJmmUTAJbaokswrPwz92342267 = -710003513;    long NivBiOXcJmmUTAJbaokswrPwz26846002 = -101187214;    long NivBiOXcJmmUTAJbaokswrPwz89314222 = -364741784;    long NivBiOXcJmmUTAJbaokswrPwz96177808 = -528028125;    long NivBiOXcJmmUTAJbaokswrPwz5920583 = -517900276;    long NivBiOXcJmmUTAJbaokswrPwz57185563 = 92113220;    long NivBiOXcJmmUTAJbaokswrPwz73129180 = -520217851;    long NivBiOXcJmmUTAJbaokswrPwz12411436 = -300688168;    long NivBiOXcJmmUTAJbaokswrPwz49663397 = -331967986;    long NivBiOXcJmmUTAJbaokswrPwz66198632 = -879429238;    long NivBiOXcJmmUTAJbaokswrPwz71412323 = -754332579;    long NivBiOXcJmmUTAJbaokswrPwz7590262 = -108784544;    long NivBiOXcJmmUTAJbaokswrPwz9388910 = -381707937;    long NivBiOXcJmmUTAJbaokswrPwz52381810 = -261036533;    long NivBiOXcJmmUTAJbaokswrPwz82185502 = -56162445;    long NivBiOXcJmmUTAJbaokswrPwz51896002 = -220442433;    long NivBiOXcJmmUTAJbaokswrPwz49428811 = -56397584;    long NivBiOXcJmmUTAJbaokswrPwz51208715 = 72002602;    long NivBiOXcJmmUTAJbaokswrPwz19449265 = 87487152;    long NivBiOXcJmmUTAJbaokswrPwz9708504 = -428905613;    long NivBiOXcJmmUTAJbaokswrPwz35085535 = -726649581;    long NivBiOXcJmmUTAJbaokswrPwz73080841 = -445159857;    long NivBiOXcJmmUTAJbaokswrPwz83166382 = -922852292;    long NivBiOXcJmmUTAJbaokswrPwz49080350 = 42986554;    long NivBiOXcJmmUTAJbaokswrPwz99299958 = -696043009;    long NivBiOXcJmmUTAJbaokswrPwz86967345 = -707652413;    long NivBiOXcJmmUTAJbaokswrPwz79018056 = -835346844;    long NivBiOXcJmmUTAJbaokswrPwz31661423 = -225016780;    long NivBiOXcJmmUTAJbaokswrPwz63951746 = -302037251;    long NivBiOXcJmmUTAJbaokswrPwz41921832 = -412486886;    long NivBiOXcJmmUTAJbaokswrPwz4625885 = -605894237;    long NivBiOXcJmmUTAJbaokswrPwz81251273 = -686315509;    long NivBiOXcJmmUTAJbaokswrPwz64352973 = -959009260;    long NivBiOXcJmmUTAJbaokswrPwz37281641 = -899551239;    long NivBiOXcJmmUTAJbaokswrPwz38413138 = -963303607;    long NivBiOXcJmmUTAJbaokswrPwz49116334 = -434164733;    long NivBiOXcJmmUTAJbaokswrPwz82776410 = -454973204;    long NivBiOXcJmmUTAJbaokswrPwz15669096 = -859428956;    long NivBiOXcJmmUTAJbaokswrPwz99854465 = -921045745;    long NivBiOXcJmmUTAJbaokswrPwz67082806 = -894443157;    long NivBiOXcJmmUTAJbaokswrPwz98882989 = -273576307;    long NivBiOXcJmmUTAJbaokswrPwz73858714 = -980890702;    long NivBiOXcJmmUTAJbaokswrPwz76152817 = -647261984;    long NivBiOXcJmmUTAJbaokswrPwz20506350 = -404538509;    long NivBiOXcJmmUTAJbaokswrPwz65054847 = 65001411;    long NivBiOXcJmmUTAJbaokswrPwz69600605 = -731411598;    long NivBiOXcJmmUTAJbaokswrPwz53817523 = -50324146;    long NivBiOXcJmmUTAJbaokswrPwz71719418 = -432259760;    long NivBiOXcJmmUTAJbaokswrPwz75975702 = 46075959;    long NivBiOXcJmmUTAJbaokswrPwz12946839 = -801489276;    long NivBiOXcJmmUTAJbaokswrPwz33042735 = -212034875;    long NivBiOXcJmmUTAJbaokswrPwz94970807 = -692613332;    long NivBiOXcJmmUTAJbaokswrPwz15940262 = -234963379;    long NivBiOXcJmmUTAJbaokswrPwz71555697 = -922824770;    long NivBiOXcJmmUTAJbaokswrPwz72187799 = -449518649;    long NivBiOXcJmmUTAJbaokswrPwz19261426 = -164843656;    long NivBiOXcJmmUTAJbaokswrPwz43679620 = -178334922;    long NivBiOXcJmmUTAJbaokswrPwz40233872 = -307728338;    long NivBiOXcJmmUTAJbaokswrPwz96877849 = -831985117;    long NivBiOXcJmmUTAJbaokswrPwz18953238 = -810247864;    long NivBiOXcJmmUTAJbaokswrPwz78167507 = -72539936;    long NivBiOXcJmmUTAJbaokswrPwz41467758 = -195201072;    long NivBiOXcJmmUTAJbaokswrPwz48459689 = -998650917;    long NivBiOXcJmmUTAJbaokswrPwz7741566 = -919481101;    long NivBiOXcJmmUTAJbaokswrPwz61572748 = -173535002;    long NivBiOXcJmmUTAJbaokswrPwz90161050 = 31982930;    long NivBiOXcJmmUTAJbaokswrPwz43237289 = -149775285;    long NivBiOXcJmmUTAJbaokswrPwz72107269 = -482156699;    long NivBiOXcJmmUTAJbaokswrPwz13968672 = -297732926;    long NivBiOXcJmmUTAJbaokswrPwz33069168 = -621997713;    long NivBiOXcJmmUTAJbaokswrPwz69119591 = -765469230;    long NivBiOXcJmmUTAJbaokswrPwz33759715 = -196968628;    long NivBiOXcJmmUTAJbaokswrPwz51354249 = -6951654;    long NivBiOXcJmmUTAJbaokswrPwz52366458 = -18069691;    long NivBiOXcJmmUTAJbaokswrPwz10825515 = -55329306;    long NivBiOXcJmmUTAJbaokswrPwz61226821 = 66208265;     NivBiOXcJmmUTAJbaokswrPwz16640800 = NivBiOXcJmmUTAJbaokswrPwz45617174;     NivBiOXcJmmUTAJbaokswrPwz45617174 = NivBiOXcJmmUTAJbaokswrPwz44554976;     NivBiOXcJmmUTAJbaokswrPwz44554976 = NivBiOXcJmmUTAJbaokswrPwz30755406;     NivBiOXcJmmUTAJbaokswrPwz30755406 = NivBiOXcJmmUTAJbaokswrPwz75962336;     NivBiOXcJmmUTAJbaokswrPwz75962336 = NivBiOXcJmmUTAJbaokswrPwz72090633;     NivBiOXcJmmUTAJbaokswrPwz72090633 = NivBiOXcJmmUTAJbaokswrPwz11846904;     NivBiOXcJmmUTAJbaokswrPwz11846904 = NivBiOXcJmmUTAJbaokswrPwz5775049;     NivBiOXcJmmUTAJbaokswrPwz5775049 = NivBiOXcJmmUTAJbaokswrPwz24268370;     NivBiOXcJmmUTAJbaokswrPwz24268370 = NivBiOXcJmmUTAJbaokswrPwz72012169;     NivBiOXcJmmUTAJbaokswrPwz72012169 = NivBiOXcJmmUTAJbaokswrPwz86270149;     NivBiOXcJmmUTAJbaokswrPwz86270149 = NivBiOXcJmmUTAJbaokswrPwz25816214;     NivBiOXcJmmUTAJbaokswrPwz25816214 = NivBiOXcJmmUTAJbaokswrPwz86704982;     NivBiOXcJmmUTAJbaokswrPwz86704982 = NivBiOXcJmmUTAJbaokswrPwz36467171;     NivBiOXcJmmUTAJbaokswrPwz36467171 = NivBiOXcJmmUTAJbaokswrPwz77190867;     NivBiOXcJmmUTAJbaokswrPwz77190867 = NivBiOXcJmmUTAJbaokswrPwz63206432;     NivBiOXcJmmUTAJbaokswrPwz63206432 = NivBiOXcJmmUTAJbaokswrPwz24101229;     NivBiOXcJmmUTAJbaokswrPwz24101229 = NivBiOXcJmmUTAJbaokswrPwz58161205;     NivBiOXcJmmUTAJbaokswrPwz58161205 = NivBiOXcJmmUTAJbaokswrPwz64842840;     NivBiOXcJmmUTAJbaokswrPwz64842840 = NivBiOXcJmmUTAJbaokswrPwz82471545;     NivBiOXcJmmUTAJbaokswrPwz82471545 = NivBiOXcJmmUTAJbaokswrPwz46179522;     NivBiOXcJmmUTAJbaokswrPwz46179522 = NivBiOXcJmmUTAJbaokswrPwz35389526;     NivBiOXcJmmUTAJbaokswrPwz35389526 = NivBiOXcJmmUTAJbaokswrPwz81264200;     NivBiOXcJmmUTAJbaokswrPwz81264200 = NivBiOXcJmmUTAJbaokswrPwz7273335;     NivBiOXcJmmUTAJbaokswrPwz7273335 = NivBiOXcJmmUTAJbaokswrPwz92342267;     NivBiOXcJmmUTAJbaokswrPwz92342267 = NivBiOXcJmmUTAJbaokswrPwz26846002;     NivBiOXcJmmUTAJbaokswrPwz26846002 = NivBiOXcJmmUTAJbaokswrPwz89314222;     NivBiOXcJmmUTAJbaokswrPwz89314222 = NivBiOXcJmmUTAJbaokswrPwz96177808;     NivBiOXcJmmUTAJbaokswrPwz96177808 = NivBiOXcJmmUTAJbaokswrPwz5920583;     NivBiOXcJmmUTAJbaokswrPwz5920583 = NivBiOXcJmmUTAJbaokswrPwz57185563;     NivBiOXcJmmUTAJbaokswrPwz57185563 = NivBiOXcJmmUTAJbaokswrPwz73129180;     NivBiOXcJmmUTAJbaokswrPwz73129180 = NivBiOXcJmmUTAJbaokswrPwz12411436;     NivBiOXcJmmUTAJbaokswrPwz12411436 = NivBiOXcJmmUTAJbaokswrPwz49663397;     NivBiOXcJmmUTAJbaokswrPwz49663397 = NivBiOXcJmmUTAJbaokswrPwz66198632;     NivBiOXcJmmUTAJbaokswrPwz66198632 = NivBiOXcJmmUTAJbaokswrPwz71412323;     NivBiOXcJmmUTAJbaokswrPwz71412323 = NivBiOXcJmmUTAJbaokswrPwz7590262;     NivBiOXcJmmUTAJbaokswrPwz7590262 = NivBiOXcJmmUTAJbaokswrPwz9388910;     NivBiOXcJmmUTAJbaokswrPwz9388910 = NivBiOXcJmmUTAJbaokswrPwz52381810;     NivBiOXcJmmUTAJbaokswrPwz52381810 = NivBiOXcJmmUTAJbaokswrPwz82185502;     NivBiOXcJmmUTAJbaokswrPwz82185502 = NivBiOXcJmmUTAJbaokswrPwz51896002;     NivBiOXcJmmUTAJbaokswrPwz51896002 = NivBiOXcJmmUTAJbaokswrPwz49428811;     NivBiOXcJmmUTAJbaokswrPwz49428811 = NivBiOXcJmmUTAJbaokswrPwz51208715;     NivBiOXcJmmUTAJbaokswrPwz51208715 = NivBiOXcJmmUTAJbaokswrPwz19449265;     NivBiOXcJmmUTAJbaokswrPwz19449265 = NivBiOXcJmmUTAJbaokswrPwz9708504;     NivBiOXcJmmUTAJbaokswrPwz9708504 = NivBiOXcJmmUTAJbaokswrPwz35085535;     NivBiOXcJmmUTAJbaokswrPwz35085535 = NivBiOXcJmmUTAJbaokswrPwz73080841;     NivBiOXcJmmUTAJbaokswrPwz73080841 = NivBiOXcJmmUTAJbaokswrPwz83166382;     NivBiOXcJmmUTAJbaokswrPwz83166382 = NivBiOXcJmmUTAJbaokswrPwz49080350;     NivBiOXcJmmUTAJbaokswrPwz49080350 = NivBiOXcJmmUTAJbaokswrPwz99299958;     NivBiOXcJmmUTAJbaokswrPwz99299958 = NivBiOXcJmmUTAJbaokswrPwz86967345;     NivBiOXcJmmUTAJbaokswrPwz86967345 = NivBiOXcJmmUTAJbaokswrPwz79018056;     NivBiOXcJmmUTAJbaokswrPwz79018056 = NivBiOXcJmmUTAJbaokswrPwz31661423;     NivBiOXcJmmUTAJbaokswrPwz31661423 = NivBiOXcJmmUTAJbaokswrPwz63951746;     NivBiOXcJmmUTAJbaokswrPwz63951746 = NivBiOXcJmmUTAJbaokswrPwz41921832;     NivBiOXcJmmUTAJbaokswrPwz41921832 = NivBiOXcJmmUTAJbaokswrPwz4625885;     NivBiOXcJmmUTAJbaokswrPwz4625885 = NivBiOXcJmmUTAJbaokswrPwz81251273;     NivBiOXcJmmUTAJbaokswrPwz81251273 = NivBiOXcJmmUTAJbaokswrPwz64352973;     NivBiOXcJmmUTAJbaokswrPwz64352973 = NivBiOXcJmmUTAJbaokswrPwz37281641;     NivBiOXcJmmUTAJbaokswrPwz37281641 = NivBiOXcJmmUTAJbaokswrPwz38413138;     NivBiOXcJmmUTAJbaokswrPwz38413138 = NivBiOXcJmmUTAJbaokswrPwz49116334;     NivBiOXcJmmUTAJbaokswrPwz49116334 = NivBiOXcJmmUTAJbaokswrPwz82776410;     NivBiOXcJmmUTAJbaokswrPwz82776410 = NivBiOXcJmmUTAJbaokswrPwz15669096;     NivBiOXcJmmUTAJbaokswrPwz15669096 = NivBiOXcJmmUTAJbaokswrPwz99854465;     NivBiOXcJmmUTAJbaokswrPwz99854465 = NivBiOXcJmmUTAJbaokswrPwz67082806;     NivBiOXcJmmUTAJbaokswrPwz67082806 = NivBiOXcJmmUTAJbaokswrPwz98882989;     NivBiOXcJmmUTAJbaokswrPwz98882989 = NivBiOXcJmmUTAJbaokswrPwz73858714;     NivBiOXcJmmUTAJbaokswrPwz73858714 = NivBiOXcJmmUTAJbaokswrPwz76152817;     NivBiOXcJmmUTAJbaokswrPwz76152817 = NivBiOXcJmmUTAJbaokswrPwz20506350;     NivBiOXcJmmUTAJbaokswrPwz20506350 = NivBiOXcJmmUTAJbaokswrPwz65054847;     NivBiOXcJmmUTAJbaokswrPwz65054847 = NivBiOXcJmmUTAJbaokswrPwz69600605;     NivBiOXcJmmUTAJbaokswrPwz69600605 = NivBiOXcJmmUTAJbaokswrPwz53817523;     NivBiOXcJmmUTAJbaokswrPwz53817523 = NivBiOXcJmmUTAJbaokswrPwz71719418;     NivBiOXcJmmUTAJbaokswrPwz71719418 = NivBiOXcJmmUTAJbaokswrPwz75975702;     NivBiOXcJmmUTAJbaokswrPwz75975702 = NivBiOXcJmmUTAJbaokswrPwz12946839;     NivBiOXcJmmUTAJbaokswrPwz12946839 = NivBiOXcJmmUTAJbaokswrPwz33042735;     NivBiOXcJmmUTAJbaokswrPwz33042735 = NivBiOXcJmmUTAJbaokswrPwz94970807;     NivBiOXcJmmUTAJbaokswrPwz94970807 = NivBiOXcJmmUTAJbaokswrPwz15940262;     NivBiOXcJmmUTAJbaokswrPwz15940262 = NivBiOXcJmmUTAJbaokswrPwz71555697;     NivBiOXcJmmUTAJbaokswrPwz71555697 = NivBiOXcJmmUTAJbaokswrPwz72187799;     NivBiOXcJmmUTAJbaokswrPwz72187799 = NivBiOXcJmmUTAJbaokswrPwz19261426;     NivBiOXcJmmUTAJbaokswrPwz19261426 = NivBiOXcJmmUTAJbaokswrPwz43679620;     NivBiOXcJmmUTAJbaokswrPwz43679620 = NivBiOXcJmmUTAJbaokswrPwz40233872;     NivBiOXcJmmUTAJbaokswrPwz40233872 = NivBiOXcJmmUTAJbaokswrPwz96877849;     NivBiOXcJmmUTAJbaokswrPwz96877849 = NivBiOXcJmmUTAJbaokswrPwz18953238;     NivBiOXcJmmUTAJbaokswrPwz18953238 = NivBiOXcJmmUTAJbaokswrPwz78167507;     NivBiOXcJmmUTAJbaokswrPwz78167507 = NivBiOXcJmmUTAJbaokswrPwz41467758;     NivBiOXcJmmUTAJbaokswrPwz41467758 = NivBiOXcJmmUTAJbaokswrPwz48459689;     NivBiOXcJmmUTAJbaokswrPwz48459689 = NivBiOXcJmmUTAJbaokswrPwz7741566;     NivBiOXcJmmUTAJbaokswrPwz7741566 = NivBiOXcJmmUTAJbaokswrPwz61572748;     NivBiOXcJmmUTAJbaokswrPwz61572748 = NivBiOXcJmmUTAJbaokswrPwz90161050;     NivBiOXcJmmUTAJbaokswrPwz90161050 = NivBiOXcJmmUTAJbaokswrPwz43237289;     NivBiOXcJmmUTAJbaokswrPwz43237289 = NivBiOXcJmmUTAJbaokswrPwz72107269;     NivBiOXcJmmUTAJbaokswrPwz72107269 = NivBiOXcJmmUTAJbaokswrPwz13968672;     NivBiOXcJmmUTAJbaokswrPwz13968672 = NivBiOXcJmmUTAJbaokswrPwz33069168;     NivBiOXcJmmUTAJbaokswrPwz33069168 = NivBiOXcJmmUTAJbaokswrPwz69119591;     NivBiOXcJmmUTAJbaokswrPwz69119591 = NivBiOXcJmmUTAJbaokswrPwz33759715;     NivBiOXcJmmUTAJbaokswrPwz33759715 = NivBiOXcJmmUTAJbaokswrPwz51354249;     NivBiOXcJmmUTAJbaokswrPwz51354249 = NivBiOXcJmmUTAJbaokswrPwz52366458;     NivBiOXcJmmUTAJbaokswrPwz52366458 = NivBiOXcJmmUTAJbaokswrPwz10825515;     NivBiOXcJmmUTAJbaokswrPwz10825515 = NivBiOXcJmmUTAJbaokswrPwz61226821;     NivBiOXcJmmUTAJbaokswrPwz61226821 = NivBiOXcJmmUTAJbaokswrPwz16640800;}
// Junk Finished
