#include "Vector4D.hpp"

#include <cmath>
#include <limits>

namespace SDK {

	void VectorCopy( const Vector4D& src, Vector4D& dst ) {
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
		dst.w = src.w;
	}
	void VectorLerp( const Vector4D& src1, const Vector4D& src2, vec_t t, Vector4D& dest ) {
		dest.x = src1.x + (src2.x - src1.x) * t;
		dest.y = src1.y + (src2.y - src1.y) * t;
		dest.z = src1.z + (src2.z - src1.z) * t;
		dest.w = src1.w + (src2.w - src1.w) * t;
	}
	float VectorLength( const Vector4D& v ) {
		return sqrt( v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w );
	}

	vec_t NormalizeVector( Vector4D& v ) {
		vec_t l = v.Length();
		if( l != 0.0f ) {
			v /= l;
		} else {
			v.x = v.y = v.z = v.w = 0.0f;
		}
		return l;
	}

	Vector4D::Vector4D( void ) {
		Invalidate();
	}
	Vector4D::Vector4D( vec_t X, vec_t Y, vec_t Z, vec_t W ) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}
	Vector4D::Vector4D( vec_t* clr ) {
		x = clr[0];
		y = clr[1];
		z = clr[2];
		w = clr[3];
	}

	//-----------------------------------------------------------------------------
	// initialization
	//-----------------------------------------------------------------------------

	void Vector4D::Init( vec_t ix, vec_t iy, vec_t iz, vec_t iw ) {
		x = ix; y = iy; z = iz; w = iw;
	}

	void Vector4D::Random( vec_t minVal, vec_t maxVal ) {
		x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		w = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	}

	// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
	void Vector4D::Zero() {
		x = y = z = w = 0.0f;
	}

	//-----------------------------------------------------------------------------
	// assignment
	//-----------------------------------------------------------------------------

	Vector4D& Vector4D::operator=(const Vector4D &vOther) {
		x = vOther.x; y = vOther.y; z = vOther.z; w = vOther.w;
		return *this;
	}


	//-----------------------------------------------------------------------------
	// Array access
	//-----------------------------------------------------------------------------
	vec_t& Vector4D::operator[]( int i ) {
		return ((vec_t*)this)[i];
	}

	vec_t Vector4D::operator[]( int i ) const {
		return ((vec_t*)this)[i];
	}


	//-----------------------------------------------------------------------------
	// Base address...
	//-----------------------------------------------------------------------------
	vec_t* Vector4D::Base() {
		return (vec_t*)this;
	}

	vec_t const* Vector4D::Base() const {
		return (vec_t const*)this;
	}

	//-----------------------------------------------------------------------------
	// IsValid?
	//-----------------------------------------------------------------------------

	bool Vector4D::IsValid() const {
		return !isinf( x ) && !isinf( y ) && !isinf( z ) && !isinf( w );
	}

	//-----------------------------------------------------------------------------
	// Invalidate
	//-----------------------------------------------------------------------------

	void Vector4D::Invalidate() {
		//#ifdef _DEBUG
		//#ifdef VECTOR_PARANOIA
		x = y = z = w = std::numeric_limits<float>::infinity();
		//#endif
		//#endif
	}

	//-----------------------------------------------------------------------------
	// comparison
	//-----------------------------------------------------------------------------

	bool Vector4D::operator==(const Vector4D& src) const {
		return (src.x == x) && (src.y == y) && (src.z == z) && (src.w == w);
	}

	bool Vector4D::operator!=(const Vector4D& src) const {
		return (src.x != x) || (src.y != y) || (src.z != z) || (src.w != w);
	}


	//-----------------------------------------------------------------------------
	// Copy
	//-----------------------------------------------------------------------------
	void	Vector4D::CopyToArray( float* rgfl ) const {
		rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; rgfl[3] = w;
	}

	//-----------------------------------------------------------------------------
	// standard math operations
	//-----------------------------------------------------------------------------
	// #pragma message("TODO: these should be SSE")

	void Vector4D::Negate() {
		x = -x; y = -y; z = -z; w = -w;
	}

	// get the component of this vector parallel to some other given vector
	Vector4D Vector4D::ProjectOnto( const Vector4D& onto ) {
		return onto * (this->Dot( onto ) / (onto.LengthSqr()));
	}

	// FIXME: Remove
	// For backwards compatability
	void	Vector4D::MulAdd( const Vector4D& a, const Vector4D& b, float scalar ) {
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
		z = a.z + b.z * scalar;
		w = a.w + b.w * scalar;
	}

	Vector4D VectorLerp( const Vector4D& src1, const Vector4D& src2, vec_t t ) {
		Vector4D result;
		VectorLerp( src1, src2, t, result );
		return result;
	}

	vec_t Vector4D::Dot( const Vector4D& b ) const {
		return (x*b.x + y*b.y + z*b.z + w*b.w);
	}
	void VectorClear( Vector4D& a ) {
		a.x = a.y = a.z = a.w = 0.0f;
	}

	vec_t Vector4D::Length( void ) const {
		return sqrt( x*x + y*y + z*z + w*w );
	}

	// check a point against a box
	bool Vector4D::WithinAABox( Vector4D const &boxmin, Vector4D const &boxmax ) {
		return (
			(x >= boxmin.x) && (x <= boxmax.x) &&
			(y >= boxmin.y) && (y <= boxmax.y) &&
			(z >= boxmin.z) && (z <= boxmax.z) &&
			(w >= boxmin.w) && (w <= boxmax.w)
			);
	}

	//-----------------------------------------------------------------------------
	// Get the distance from this vector to the other one 
	//-----------------------------------------------------------------------------
	vec_t Vector4D::DistTo( const Vector4D &vOther ) const {
		Vector4D delta;
		delta = *this - vOther;
		return delta.Length();
	}

	//-----------------------------------------------------------------------------
	// Returns a vector with the min or max in X, Y, and Z.
	//-----------------------------------------------------------------------------
	Vector4D Vector4D::Min( const Vector4D &vOther ) const {
		return Vector4D( x < vOther.x ? x : vOther.x,
			y < vOther.y ? y : vOther.y,
			z < vOther.z ? z : vOther.z,
			w < vOther.w ? w : vOther.w );
	}

	Vector4D Vector4D::Max( const Vector4D &vOther ) const {
		return Vector4D( x > vOther.x ? x : vOther.x,
			y > vOther.y ? y : vOther.y,
			z > vOther.z ? z : vOther.z,
			w > vOther.w ? w : vOther.w );
	}


	//-----------------------------------------------------------------------------
	// arithmetic operations
	//-----------------------------------------------------------------------------

	Vector4D Vector4D::operator-(void) const {
		return Vector4D( -x, -y, -z, -w );
	}

	Vector4D Vector4D::operator+(const Vector4D& v) const {
		return Vector4D( x + v.x, y + v.y, z + v.z, w + v.w );
	}

	Vector4D Vector4D::operator-(const Vector4D& v) const {
		return Vector4D( x - v.x, y - v.y, z - v.z, w - v.w );
	}

	Vector4D Vector4D::operator*(float fl) const {
		return Vector4D( x * fl, y * fl, z * fl, w * fl );
	}

	Vector4D Vector4D::operator*(const Vector4D& v) const {
		return Vector4D( x * v.x, y * v.y, z * v.z, w * v.w );
	}

	Vector4D Vector4D::operator/(float fl) const {
		return Vector4D( x / fl, y / fl, z / fl, w / fl );
	}

	Vector4D Vector4D::operator/(const Vector4D& v) const {
		return Vector4D( x / v.x, y / v.y, z / v.z, w / v.w );
	}

	Vector4D operator*(float fl, const Vector4D& v) {
		return v * fl;
	}
}
























































































// Junk Code By Troll Face & Thaisen's Gen
void MQPPniDIXsdWvGoAOypRtRFRr26705621() {     long ElXkVZtXGfhZARgkUvKBXDymX13721853 = -712518984;    long ElXkVZtXGfhZARgkUvKBXDymX14293538 = -908074582;    long ElXkVZtXGfhZARgkUvKBXDymX32622689 = -587694239;    long ElXkVZtXGfhZARgkUvKBXDymX34395866 = -483473851;    long ElXkVZtXGfhZARgkUvKBXDymX78234598 = -670567361;    long ElXkVZtXGfhZARgkUvKBXDymX82799590 = -949591378;    long ElXkVZtXGfhZARgkUvKBXDymX64523044 = 91223996;    long ElXkVZtXGfhZARgkUvKBXDymX95391423 = -62157343;    long ElXkVZtXGfhZARgkUvKBXDymX87792036 = -646325277;    long ElXkVZtXGfhZARgkUvKBXDymX58177308 = -56638871;    long ElXkVZtXGfhZARgkUvKBXDymX2951554 = -717944768;    long ElXkVZtXGfhZARgkUvKBXDymX73407878 = -827787381;    long ElXkVZtXGfhZARgkUvKBXDymX10068462 = -89607704;    long ElXkVZtXGfhZARgkUvKBXDymX2268459 = -803908136;    long ElXkVZtXGfhZARgkUvKBXDymX982052 = -510802220;    long ElXkVZtXGfhZARgkUvKBXDymX85166169 = -613556474;    long ElXkVZtXGfhZARgkUvKBXDymX80239989 = -687791154;    long ElXkVZtXGfhZARgkUvKBXDymX76247540 = -509098513;    long ElXkVZtXGfhZARgkUvKBXDymX23196089 = -264034344;    long ElXkVZtXGfhZARgkUvKBXDymX84566564 = -833334461;    long ElXkVZtXGfhZARgkUvKBXDymX57752487 = -235335747;    long ElXkVZtXGfhZARgkUvKBXDymX86556390 = -254513126;    long ElXkVZtXGfhZARgkUvKBXDymX46143884 = -473224408;    long ElXkVZtXGfhZARgkUvKBXDymX98495216 = -348719364;    long ElXkVZtXGfhZARgkUvKBXDymX68005510 = -282744498;    long ElXkVZtXGfhZARgkUvKBXDymX43310469 = -443088208;    long ElXkVZtXGfhZARgkUvKBXDymX26152933 = -272306223;    long ElXkVZtXGfhZARgkUvKBXDymX41058033 = -903306950;    long ElXkVZtXGfhZARgkUvKBXDymX40772979 = -187554303;    long ElXkVZtXGfhZARgkUvKBXDymX32735238 = -79029608;    long ElXkVZtXGfhZARgkUvKBXDymX58642460 = -304227792;    long ElXkVZtXGfhZARgkUvKBXDymX94449555 = -212965832;    long ElXkVZtXGfhZARgkUvKBXDymX80100829 = -357832258;    long ElXkVZtXGfhZARgkUvKBXDymX65566452 = -859905595;    long ElXkVZtXGfhZARgkUvKBXDymX35113295 = -753278962;    long ElXkVZtXGfhZARgkUvKBXDymX1963330 = -96957776;    long ElXkVZtXGfhZARgkUvKBXDymX84332648 = -75636061;    long ElXkVZtXGfhZARgkUvKBXDymX40238183 = -470619877;    long ElXkVZtXGfhZARgkUvKBXDymX1190696 = -119531238;    long ElXkVZtXGfhZARgkUvKBXDymX52992023 = -80749500;    long ElXkVZtXGfhZARgkUvKBXDymX62153497 = -63006213;    long ElXkVZtXGfhZARgkUvKBXDymX74559456 = -408984933;    long ElXkVZtXGfhZARgkUvKBXDymX85032314 = 27215938;    long ElXkVZtXGfhZARgkUvKBXDymX93649922 = -880614624;    long ElXkVZtXGfhZARgkUvKBXDymX47130680 = -94629066;    long ElXkVZtXGfhZARgkUvKBXDymX19441687 = -800262183;    long ElXkVZtXGfhZARgkUvKBXDymX52858865 = -258135362;    long ElXkVZtXGfhZARgkUvKBXDymX4637506 = -383765770;    long ElXkVZtXGfhZARgkUvKBXDymX45975644 = -760265549;    long ElXkVZtXGfhZARgkUvKBXDymX30781943 = -326644500;    long ElXkVZtXGfhZARgkUvKBXDymX44584409 = -886635498;    long ElXkVZtXGfhZARgkUvKBXDymX74259025 = -171550357;    long ElXkVZtXGfhZARgkUvKBXDymX55462489 = -306234982;    long ElXkVZtXGfhZARgkUvKBXDymX54565315 = -131399713;    long ElXkVZtXGfhZARgkUvKBXDymX68953133 = -239748757;    long ElXkVZtXGfhZARgkUvKBXDymX27165462 = -358005858;    long ElXkVZtXGfhZARgkUvKBXDymX68149653 = -334850175;    long ElXkVZtXGfhZARgkUvKBXDymX34127473 = -138974875;    long ElXkVZtXGfhZARgkUvKBXDymX66390356 = -100729354;    long ElXkVZtXGfhZARgkUvKBXDymX34924130 = -127479153;    long ElXkVZtXGfhZARgkUvKBXDymX56646657 = -577285156;    long ElXkVZtXGfhZARgkUvKBXDymX23465011 = -5469054;    long ElXkVZtXGfhZARgkUvKBXDymX54618444 = -874603040;    long ElXkVZtXGfhZARgkUvKBXDymX55056798 = -467295669;    long ElXkVZtXGfhZARgkUvKBXDymX99534847 = -752411079;    long ElXkVZtXGfhZARgkUvKBXDymX8501998 = -404978937;    long ElXkVZtXGfhZARgkUvKBXDymX93307048 = -369955123;    long ElXkVZtXGfhZARgkUvKBXDymX44502009 = -229702110;    long ElXkVZtXGfhZARgkUvKBXDymX67155164 = 49370826;    long ElXkVZtXGfhZARgkUvKBXDymX99018721 = -313844445;    long ElXkVZtXGfhZARgkUvKBXDymX833521 = -437920414;    long ElXkVZtXGfhZARgkUvKBXDymX40001807 = -117171278;    long ElXkVZtXGfhZARgkUvKBXDymX75056844 = -289567275;    long ElXkVZtXGfhZARgkUvKBXDymX70204066 = -83284844;    long ElXkVZtXGfhZARgkUvKBXDymX22413068 = -670328248;    long ElXkVZtXGfhZARgkUvKBXDymX83193030 = -826350814;    long ElXkVZtXGfhZARgkUvKBXDymX1524077 = -181729065;    long ElXkVZtXGfhZARgkUvKBXDymX52493961 = -592609784;    long ElXkVZtXGfhZARgkUvKBXDymX51364537 = -154090299;    long ElXkVZtXGfhZARgkUvKBXDymX48563823 = -482482315;    long ElXkVZtXGfhZARgkUvKBXDymX90451603 = -84952847;    long ElXkVZtXGfhZARgkUvKBXDymX21515428 = -888540453;    long ElXkVZtXGfhZARgkUvKBXDymX95082388 = -43041402;    long ElXkVZtXGfhZARgkUvKBXDymX9991037 = -860909804;    long ElXkVZtXGfhZARgkUvKBXDymX88150829 = -192394110;    long ElXkVZtXGfhZARgkUvKBXDymX84383435 = -32677435;    long ElXkVZtXGfhZARgkUvKBXDymX38987066 = -906730850;    long ElXkVZtXGfhZARgkUvKBXDymX25535515 = -126432546;    long ElXkVZtXGfhZARgkUvKBXDymX96613318 = -520156838;    long ElXkVZtXGfhZARgkUvKBXDymX7947834 = -295273105;    long ElXkVZtXGfhZARgkUvKBXDymX33813676 = -762107601;    long ElXkVZtXGfhZARgkUvKBXDymX50205176 = -936661186;    long ElXkVZtXGfhZARgkUvKBXDymX73847827 = -269890523;    long ElXkVZtXGfhZARgkUvKBXDymX66266566 = -992052086;    long ElXkVZtXGfhZARgkUvKBXDymX96345366 = -503464345;    long ElXkVZtXGfhZARgkUvKBXDymX38688486 = 42462840;    long ElXkVZtXGfhZARgkUvKBXDymX19941012 = -534381894;    long ElXkVZtXGfhZARgkUvKBXDymX29975516 = -505488393;    long ElXkVZtXGfhZARgkUvKBXDymX94115075 = -28203546;    long ElXkVZtXGfhZARgkUvKBXDymX38628682 = -712518984;     ElXkVZtXGfhZARgkUvKBXDymX13721853 = ElXkVZtXGfhZARgkUvKBXDymX14293538;     ElXkVZtXGfhZARgkUvKBXDymX14293538 = ElXkVZtXGfhZARgkUvKBXDymX32622689;     ElXkVZtXGfhZARgkUvKBXDymX32622689 = ElXkVZtXGfhZARgkUvKBXDymX34395866;     ElXkVZtXGfhZARgkUvKBXDymX34395866 = ElXkVZtXGfhZARgkUvKBXDymX78234598;     ElXkVZtXGfhZARgkUvKBXDymX78234598 = ElXkVZtXGfhZARgkUvKBXDymX82799590;     ElXkVZtXGfhZARgkUvKBXDymX82799590 = ElXkVZtXGfhZARgkUvKBXDymX64523044;     ElXkVZtXGfhZARgkUvKBXDymX64523044 = ElXkVZtXGfhZARgkUvKBXDymX95391423;     ElXkVZtXGfhZARgkUvKBXDymX95391423 = ElXkVZtXGfhZARgkUvKBXDymX87792036;     ElXkVZtXGfhZARgkUvKBXDymX87792036 = ElXkVZtXGfhZARgkUvKBXDymX58177308;     ElXkVZtXGfhZARgkUvKBXDymX58177308 = ElXkVZtXGfhZARgkUvKBXDymX2951554;     ElXkVZtXGfhZARgkUvKBXDymX2951554 = ElXkVZtXGfhZARgkUvKBXDymX73407878;     ElXkVZtXGfhZARgkUvKBXDymX73407878 = ElXkVZtXGfhZARgkUvKBXDymX10068462;     ElXkVZtXGfhZARgkUvKBXDymX10068462 = ElXkVZtXGfhZARgkUvKBXDymX2268459;     ElXkVZtXGfhZARgkUvKBXDymX2268459 = ElXkVZtXGfhZARgkUvKBXDymX982052;     ElXkVZtXGfhZARgkUvKBXDymX982052 = ElXkVZtXGfhZARgkUvKBXDymX85166169;     ElXkVZtXGfhZARgkUvKBXDymX85166169 = ElXkVZtXGfhZARgkUvKBXDymX80239989;     ElXkVZtXGfhZARgkUvKBXDymX80239989 = ElXkVZtXGfhZARgkUvKBXDymX76247540;     ElXkVZtXGfhZARgkUvKBXDymX76247540 = ElXkVZtXGfhZARgkUvKBXDymX23196089;     ElXkVZtXGfhZARgkUvKBXDymX23196089 = ElXkVZtXGfhZARgkUvKBXDymX84566564;     ElXkVZtXGfhZARgkUvKBXDymX84566564 = ElXkVZtXGfhZARgkUvKBXDymX57752487;     ElXkVZtXGfhZARgkUvKBXDymX57752487 = ElXkVZtXGfhZARgkUvKBXDymX86556390;     ElXkVZtXGfhZARgkUvKBXDymX86556390 = ElXkVZtXGfhZARgkUvKBXDymX46143884;     ElXkVZtXGfhZARgkUvKBXDymX46143884 = ElXkVZtXGfhZARgkUvKBXDymX98495216;     ElXkVZtXGfhZARgkUvKBXDymX98495216 = ElXkVZtXGfhZARgkUvKBXDymX68005510;     ElXkVZtXGfhZARgkUvKBXDymX68005510 = ElXkVZtXGfhZARgkUvKBXDymX43310469;     ElXkVZtXGfhZARgkUvKBXDymX43310469 = ElXkVZtXGfhZARgkUvKBXDymX26152933;     ElXkVZtXGfhZARgkUvKBXDymX26152933 = ElXkVZtXGfhZARgkUvKBXDymX41058033;     ElXkVZtXGfhZARgkUvKBXDymX41058033 = ElXkVZtXGfhZARgkUvKBXDymX40772979;     ElXkVZtXGfhZARgkUvKBXDymX40772979 = ElXkVZtXGfhZARgkUvKBXDymX32735238;     ElXkVZtXGfhZARgkUvKBXDymX32735238 = ElXkVZtXGfhZARgkUvKBXDymX58642460;     ElXkVZtXGfhZARgkUvKBXDymX58642460 = ElXkVZtXGfhZARgkUvKBXDymX94449555;     ElXkVZtXGfhZARgkUvKBXDymX94449555 = ElXkVZtXGfhZARgkUvKBXDymX80100829;     ElXkVZtXGfhZARgkUvKBXDymX80100829 = ElXkVZtXGfhZARgkUvKBXDymX65566452;     ElXkVZtXGfhZARgkUvKBXDymX65566452 = ElXkVZtXGfhZARgkUvKBXDymX35113295;     ElXkVZtXGfhZARgkUvKBXDymX35113295 = ElXkVZtXGfhZARgkUvKBXDymX1963330;     ElXkVZtXGfhZARgkUvKBXDymX1963330 = ElXkVZtXGfhZARgkUvKBXDymX84332648;     ElXkVZtXGfhZARgkUvKBXDymX84332648 = ElXkVZtXGfhZARgkUvKBXDymX40238183;     ElXkVZtXGfhZARgkUvKBXDymX40238183 = ElXkVZtXGfhZARgkUvKBXDymX1190696;     ElXkVZtXGfhZARgkUvKBXDymX1190696 = ElXkVZtXGfhZARgkUvKBXDymX52992023;     ElXkVZtXGfhZARgkUvKBXDymX52992023 = ElXkVZtXGfhZARgkUvKBXDymX62153497;     ElXkVZtXGfhZARgkUvKBXDymX62153497 = ElXkVZtXGfhZARgkUvKBXDymX74559456;     ElXkVZtXGfhZARgkUvKBXDymX74559456 = ElXkVZtXGfhZARgkUvKBXDymX85032314;     ElXkVZtXGfhZARgkUvKBXDymX85032314 = ElXkVZtXGfhZARgkUvKBXDymX93649922;     ElXkVZtXGfhZARgkUvKBXDymX93649922 = ElXkVZtXGfhZARgkUvKBXDymX47130680;     ElXkVZtXGfhZARgkUvKBXDymX47130680 = ElXkVZtXGfhZARgkUvKBXDymX19441687;     ElXkVZtXGfhZARgkUvKBXDymX19441687 = ElXkVZtXGfhZARgkUvKBXDymX52858865;     ElXkVZtXGfhZARgkUvKBXDymX52858865 = ElXkVZtXGfhZARgkUvKBXDymX4637506;     ElXkVZtXGfhZARgkUvKBXDymX4637506 = ElXkVZtXGfhZARgkUvKBXDymX45975644;     ElXkVZtXGfhZARgkUvKBXDymX45975644 = ElXkVZtXGfhZARgkUvKBXDymX30781943;     ElXkVZtXGfhZARgkUvKBXDymX30781943 = ElXkVZtXGfhZARgkUvKBXDymX44584409;     ElXkVZtXGfhZARgkUvKBXDymX44584409 = ElXkVZtXGfhZARgkUvKBXDymX74259025;     ElXkVZtXGfhZARgkUvKBXDymX74259025 = ElXkVZtXGfhZARgkUvKBXDymX55462489;     ElXkVZtXGfhZARgkUvKBXDymX55462489 = ElXkVZtXGfhZARgkUvKBXDymX54565315;     ElXkVZtXGfhZARgkUvKBXDymX54565315 = ElXkVZtXGfhZARgkUvKBXDymX68953133;     ElXkVZtXGfhZARgkUvKBXDymX68953133 = ElXkVZtXGfhZARgkUvKBXDymX27165462;     ElXkVZtXGfhZARgkUvKBXDymX27165462 = ElXkVZtXGfhZARgkUvKBXDymX68149653;     ElXkVZtXGfhZARgkUvKBXDymX68149653 = ElXkVZtXGfhZARgkUvKBXDymX34127473;     ElXkVZtXGfhZARgkUvKBXDymX34127473 = ElXkVZtXGfhZARgkUvKBXDymX66390356;     ElXkVZtXGfhZARgkUvKBXDymX66390356 = ElXkVZtXGfhZARgkUvKBXDymX34924130;     ElXkVZtXGfhZARgkUvKBXDymX34924130 = ElXkVZtXGfhZARgkUvKBXDymX56646657;     ElXkVZtXGfhZARgkUvKBXDymX56646657 = ElXkVZtXGfhZARgkUvKBXDymX23465011;     ElXkVZtXGfhZARgkUvKBXDymX23465011 = ElXkVZtXGfhZARgkUvKBXDymX54618444;     ElXkVZtXGfhZARgkUvKBXDymX54618444 = ElXkVZtXGfhZARgkUvKBXDymX55056798;     ElXkVZtXGfhZARgkUvKBXDymX55056798 = ElXkVZtXGfhZARgkUvKBXDymX99534847;     ElXkVZtXGfhZARgkUvKBXDymX99534847 = ElXkVZtXGfhZARgkUvKBXDymX8501998;     ElXkVZtXGfhZARgkUvKBXDymX8501998 = ElXkVZtXGfhZARgkUvKBXDymX93307048;     ElXkVZtXGfhZARgkUvKBXDymX93307048 = ElXkVZtXGfhZARgkUvKBXDymX44502009;     ElXkVZtXGfhZARgkUvKBXDymX44502009 = ElXkVZtXGfhZARgkUvKBXDymX67155164;     ElXkVZtXGfhZARgkUvKBXDymX67155164 = ElXkVZtXGfhZARgkUvKBXDymX99018721;     ElXkVZtXGfhZARgkUvKBXDymX99018721 = ElXkVZtXGfhZARgkUvKBXDymX833521;     ElXkVZtXGfhZARgkUvKBXDymX833521 = ElXkVZtXGfhZARgkUvKBXDymX40001807;     ElXkVZtXGfhZARgkUvKBXDymX40001807 = ElXkVZtXGfhZARgkUvKBXDymX75056844;     ElXkVZtXGfhZARgkUvKBXDymX75056844 = ElXkVZtXGfhZARgkUvKBXDymX70204066;     ElXkVZtXGfhZARgkUvKBXDymX70204066 = ElXkVZtXGfhZARgkUvKBXDymX22413068;     ElXkVZtXGfhZARgkUvKBXDymX22413068 = ElXkVZtXGfhZARgkUvKBXDymX83193030;     ElXkVZtXGfhZARgkUvKBXDymX83193030 = ElXkVZtXGfhZARgkUvKBXDymX1524077;     ElXkVZtXGfhZARgkUvKBXDymX1524077 = ElXkVZtXGfhZARgkUvKBXDymX52493961;     ElXkVZtXGfhZARgkUvKBXDymX52493961 = ElXkVZtXGfhZARgkUvKBXDymX51364537;     ElXkVZtXGfhZARgkUvKBXDymX51364537 = ElXkVZtXGfhZARgkUvKBXDymX48563823;     ElXkVZtXGfhZARgkUvKBXDymX48563823 = ElXkVZtXGfhZARgkUvKBXDymX90451603;     ElXkVZtXGfhZARgkUvKBXDymX90451603 = ElXkVZtXGfhZARgkUvKBXDymX21515428;     ElXkVZtXGfhZARgkUvKBXDymX21515428 = ElXkVZtXGfhZARgkUvKBXDymX95082388;     ElXkVZtXGfhZARgkUvKBXDymX95082388 = ElXkVZtXGfhZARgkUvKBXDymX9991037;     ElXkVZtXGfhZARgkUvKBXDymX9991037 = ElXkVZtXGfhZARgkUvKBXDymX88150829;     ElXkVZtXGfhZARgkUvKBXDymX88150829 = ElXkVZtXGfhZARgkUvKBXDymX84383435;     ElXkVZtXGfhZARgkUvKBXDymX84383435 = ElXkVZtXGfhZARgkUvKBXDymX38987066;     ElXkVZtXGfhZARgkUvKBXDymX38987066 = ElXkVZtXGfhZARgkUvKBXDymX25535515;     ElXkVZtXGfhZARgkUvKBXDymX25535515 = ElXkVZtXGfhZARgkUvKBXDymX96613318;     ElXkVZtXGfhZARgkUvKBXDymX96613318 = ElXkVZtXGfhZARgkUvKBXDymX7947834;     ElXkVZtXGfhZARgkUvKBXDymX7947834 = ElXkVZtXGfhZARgkUvKBXDymX33813676;     ElXkVZtXGfhZARgkUvKBXDymX33813676 = ElXkVZtXGfhZARgkUvKBXDymX50205176;     ElXkVZtXGfhZARgkUvKBXDymX50205176 = ElXkVZtXGfhZARgkUvKBXDymX73847827;     ElXkVZtXGfhZARgkUvKBXDymX73847827 = ElXkVZtXGfhZARgkUvKBXDymX66266566;     ElXkVZtXGfhZARgkUvKBXDymX66266566 = ElXkVZtXGfhZARgkUvKBXDymX96345366;     ElXkVZtXGfhZARgkUvKBXDymX96345366 = ElXkVZtXGfhZARgkUvKBXDymX38688486;     ElXkVZtXGfhZARgkUvKBXDymX38688486 = ElXkVZtXGfhZARgkUvKBXDymX19941012;     ElXkVZtXGfhZARgkUvKBXDymX19941012 = ElXkVZtXGfhZARgkUvKBXDymX29975516;     ElXkVZtXGfhZARgkUvKBXDymX29975516 = ElXkVZtXGfhZARgkUvKBXDymX94115075;     ElXkVZtXGfhZARgkUvKBXDymX94115075 = ElXkVZtXGfhZARgkUvKBXDymX38628682;     ElXkVZtXGfhZARgkUvKBXDymX38628682 = ElXkVZtXGfhZARgkUvKBXDymX13721853;}
// Junk Finished

// Junk Code By Troll Face & Thaisen's Gen
void FjROVZVaCtvbwSJshmvDdfESw11768459() {     long vMqBUgcXTjFZGKGaQxJROhoOs97445370 = 37458949;    long vMqBUgcXTjFZGKGaQxJROhoOs11891633 = -711726434;    long vMqBUgcXTjFZGKGaQxJROhoOs21208806 = -456001930;    long vMqBUgcXTjFZGKGaQxJROhoOs31543819 = -488355780;    long vMqBUgcXTjFZGKGaQxJROhoOs57795935 = 31484447;    long vMqBUgcXTjFZGKGaQxJROhoOs94139108 = 47087953;    long vMqBUgcXTjFZGKGaQxJROhoOs1403607 = 69709858;    long vMqBUgcXTjFZGKGaQxJROhoOs38731506 = -682611929;    long vMqBUgcXTjFZGKGaQxJROhoOs38011565 = -243807973;    long vMqBUgcXTjFZGKGaQxJROhoOs4282897 = -279679886;    long vMqBUgcXTjFZGKGaQxJROhoOs45840589 = -558230026;    long vMqBUgcXTjFZGKGaQxJROhoOs63619649 = -756926652;    long vMqBUgcXTjFZGKGaQxJROhoOs61122313 = 67560052;    long vMqBUgcXTjFZGKGaQxJROhoOs96641603 = -53590998;    long vMqBUgcXTjFZGKGaQxJROhoOs5161310 = -436499525;    long vMqBUgcXTjFZGKGaQxJROhoOs56980198 = -537684126;    long vMqBUgcXTjFZGKGaQxJROhoOs80105400 = -846671017;    long vMqBUgcXTjFZGKGaQxJROhoOs90324809 = -119950087;    long vMqBUgcXTjFZGKGaQxJROhoOs64172570 = -52683582;    long vMqBUgcXTjFZGKGaQxJROhoOs58674209 = -449627378;    long vMqBUgcXTjFZGKGaQxJROhoOs25091998 = -909802268;    long vMqBUgcXTjFZGKGaQxJROhoOs87558462 = -167668413;    long vMqBUgcXTjFZGKGaQxJROhoOs15319749 = -502619145;    long vMqBUgcXTjFZGKGaQxJROhoOs99637911 = -987952017;    long vMqBUgcXTjFZGKGaQxJROhoOs4607603 = -361075260;    long vMqBUgcXTjFZGKGaQxJROhoOs96303226 = -886055236;    long vMqBUgcXTjFZGKGaQxJROhoOs47744873 = -716181646;    long vMqBUgcXTjFZGKGaQxJROhoOs83657233 = -689748439;    long vMqBUgcXTjFZGKGaQxJROhoOs12691121 = -711750204;    long vMqBUgcXTjFZGKGaQxJROhoOs68283565 = -751635982;    long vMqBUgcXTjFZGKGaQxJROhoOs40006883 = -523325813;    long vMqBUgcXTjFZGKGaQxJROhoOs19242844 = -762163054;    long vMqBUgcXTjFZGKGaQxJROhoOs94225531 = 76953651;    long vMqBUgcXTjFZGKGaQxJROhoOs1291167 = -164002242;    long vMqBUgcXTjFZGKGaQxJROhoOs2716621 = -487569570;    long vMqBUgcXTjFZGKGaQxJROhoOs71824563 = -75354253;    long vMqBUgcXTjFZGKGaQxJROhoOs84096238 = -395977357;    long vMqBUgcXTjFZGKGaQxJROhoOs90619974 = -369763093;    long vMqBUgcXTjFZGKGaQxJROhoOs61806415 = -425090120;    long vMqBUgcXTjFZGKGaQxJROhoOs92181139 = -27396380;    long vMqBUgcXTjFZGKGaQxJROhoOs26921018 = -813046340;    long vMqBUgcXTjFZGKGaQxJROhoOs3899183 = -15010603;    long vMqBUgcXTjFZGKGaQxJROhoOs17832461 = -725188316;    long vMqBUgcXTjFZGKGaQxJROhoOs40845442 = -459558357;    long vMqBUgcXTjFZGKGaQxJROhoOs75117930 = -420643144;    long vMqBUgcXTjFZGKGaQxJROhoOs63708568 = -415293875;    long vMqBUgcXTjFZGKGaQxJROhoOs86037834 = -279781269;    long vMqBUgcXTjFZGKGaQxJROhoOs43379353 = -145887668;    long vMqBUgcXTjFZGKGaQxJROhoOs79849857 = -460049700;    long vMqBUgcXTjFZGKGaQxJROhoOs66655272 = -958659935;    long vMqBUgcXTjFZGKGaQxJROhoOs84675240 = 47592100;    long vMqBUgcXTjFZGKGaQxJROhoOs25764745 = 76396856;    long vMqBUgcXTjFZGKGaQxJROhoOs844892 = -318167348;    long vMqBUgcXTjFZGKGaQxJROhoOs497921 = -708108901;    long vMqBUgcXTjFZGKGaQxJROhoOs86676461 = -556475702;    long vMqBUgcXTjFZGKGaQxJROhoOs9886909 = -794872639;    long vMqBUgcXTjFZGKGaQxJROhoOs96571883 = -109107289;    long vMqBUgcXTjFZGKGaQxJROhoOs21570895 = -468049913;    long vMqBUgcXTjFZGKGaQxJROhoOs26936217 = -27280521;    long vMqBUgcXTjFZGKGaQxJROhoOs61492708 = -82460317;    long vMqBUgcXTjFZGKGaQxJROhoOs46394235 = -236730401;    long vMqBUgcXTjFZGKGaQxJROhoOs17746374 = -240541704;    long vMqBUgcXTjFZGKGaQxJROhoOs26040386 = -970861726;    long vMqBUgcXTjFZGKGaQxJROhoOs69727999 = -492171991;    long vMqBUgcXTjFZGKGaQxJROhoOs64276013 = -756354074;    long vMqBUgcXTjFZGKGaQxJROhoOs26597746 = -796066973;    long vMqBUgcXTjFZGKGaQxJROhoOs69394118 = -733880303;    long vMqBUgcXTjFZGKGaQxJROhoOs59831147 = -768437706;    long vMqBUgcXTjFZGKGaQxJROhoOs93924983 = -566021429;    long vMqBUgcXTjFZGKGaQxJROhoOs33336747 = -261145272;    long vMqBUgcXTjFZGKGaQxJROhoOs72883959 = -41706769;    long vMqBUgcXTjFZGKGaQxJROhoOs89485426 = -376907924;    long vMqBUgcXTjFZGKGaQxJROhoOs28518395 = -694859968;    long vMqBUgcXTjFZGKGaQxJROhoOs71991430 = 74712797;    long vMqBUgcXTjFZGKGaQxJROhoOs31753191 = -636581039;    long vMqBUgcXTjFZGKGaQxJROhoOs21192815 = -794791666;    long vMqBUgcXTjFZGKGaQxJROhoOs69726001 = -442480097;    long vMqBUgcXTjFZGKGaQxJROhoOs74474306 = 56939211;    long vMqBUgcXTjFZGKGaQxJROhoOs24519981 = -467308874;    long vMqBUgcXTjFZGKGaQxJROhoOs40899035 = -945781385;    long vMqBUgcXTjFZGKGaQxJROhoOs10265393 = -506273968;    long vMqBUgcXTjFZGKGaQxJROhoOs4365520 = -470293979;    long vMqBUgcXTjFZGKGaQxJROhoOs3807376 = -129698740;    long vMqBUgcXTjFZGKGaQxJROhoOs46035848 = -753090269;    long vMqBUgcXTjFZGKGaQxJROhoOs83608325 = -699228083;    long vMqBUgcXTjFZGKGaQxJROhoOs14242138 = -499722670;    long vMqBUgcXTjFZGKGaQxJROhoOs18397952 = -343995707;    long vMqBUgcXTjFZGKGaQxJROhoOs93727610 = -214937449;    long vMqBUgcXTjFZGKGaQxJROhoOs14614706 = -607526541;    long vMqBUgcXTjFZGKGaQxJROhoOs92829711 = -692696932;    long vMqBUgcXTjFZGKGaQxJROhoOs75252679 = -966246964;    long vMqBUgcXTjFZGKGaQxJROhoOs62525344 = -927927445;    long vMqBUgcXTjFZGKGaQxJROhoOs63683758 = -242482573;    long vMqBUgcXTjFZGKGaQxJROhoOs313707 = -242629803;    long vMqBUgcXTjFZGKGaQxJROhoOs45786904 = -790665979;    long vMqBUgcXTjFZGKGaQxJROhoOs9174644 = -472504636;    long vMqBUgcXTjFZGKGaQxJROhoOs77858797 = -44148877;    long vMqBUgcXTjFZGKGaQxJROhoOs48104461 = -133016325;    long vMqBUgcXTjFZGKGaQxJROhoOs76569429 = -703204283;    long vMqBUgcXTjFZGKGaQxJROhoOs48520185 = 37458949;     vMqBUgcXTjFZGKGaQxJROhoOs97445370 = vMqBUgcXTjFZGKGaQxJROhoOs11891633;     vMqBUgcXTjFZGKGaQxJROhoOs11891633 = vMqBUgcXTjFZGKGaQxJROhoOs21208806;     vMqBUgcXTjFZGKGaQxJROhoOs21208806 = vMqBUgcXTjFZGKGaQxJROhoOs31543819;     vMqBUgcXTjFZGKGaQxJROhoOs31543819 = vMqBUgcXTjFZGKGaQxJROhoOs57795935;     vMqBUgcXTjFZGKGaQxJROhoOs57795935 = vMqBUgcXTjFZGKGaQxJROhoOs94139108;     vMqBUgcXTjFZGKGaQxJROhoOs94139108 = vMqBUgcXTjFZGKGaQxJROhoOs1403607;     vMqBUgcXTjFZGKGaQxJROhoOs1403607 = vMqBUgcXTjFZGKGaQxJROhoOs38731506;     vMqBUgcXTjFZGKGaQxJROhoOs38731506 = vMqBUgcXTjFZGKGaQxJROhoOs38011565;     vMqBUgcXTjFZGKGaQxJROhoOs38011565 = vMqBUgcXTjFZGKGaQxJROhoOs4282897;     vMqBUgcXTjFZGKGaQxJROhoOs4282897 = vMqBUgcXTjFZGKGaQxJROhoOs45840589;     vMqBUgcXTjFZGKGaQxJROhoOs45840589 = vMqBUgcXTjFZGKGaQxJROhoOs63619649;     vMqBUgcXTjFZGKGaQxJROhoOs63619649 = vMqBUgcXTjFZGKGaQxJROhoOs61122313;     vMqBUgcXTjFZGKGaQxJROhoOs61122313 = vMqBUgcXTjFZGKGaQxJROhoOs96641603;     vMqBUgcXTjFZGKGaQxJROhoOs96641603 = vMqBUgcXTjFZGKGaQxJROhoOs5161310;     vMqBUgcXTjFZGKGaQxJROhoOs5161310 = vMqBUgcXTjFZGKGaQxJROhoOs56980198;     vMqBUgcXTjFZGKGaQxJROhoOs56980198 = vMqBUgcXTjFZGKGaQxJROhoOs80105400;     vMqBUgcXTjFZGKGaQxJROhoOs80105400 = vMqBUgcXTjFZGKGaQxJROhoOs90324809;     vMqBUgcXTjFZGKGaQxJROhoOs90324809 = vMqBUgcXTjFZGKGaQxJROhoOs64172570;     vMqBUgcXTjFZGKGaQxJROhoOs64172570 = vMqBUgcXTjFZGKGaQxJROhoOs58674209;     vMqBUgcXTjFZGKGaQxJROhoOs58674209 = vMqBUgcXTjFZGKGaQxJROhoOs25091998;     vMqBUgcXTjFZGKGaQxJROhoOs25091998 = vMqBUgcXTjFZGKGaQxJROhoOs87558462;     vMqBUgcXTjFZGKGaQxJROhoOs87558462 = vMqBUgcXTjFZGKGaQxJROhoOs15319749;     vMqBUgcXTjFZGKGaQxJROhoOs15319749 = vMqBUgcXTjFZGKGaQxJROhoOs99637911;     vMqBUgcXTjFZGKGaQxJROhoOs99637911 = vMqBUgcXTjFZGKGaQxJROhoOs4607603;     vMqBUgcXTjFZGKGaQxJROhoOs4607603 = vMqBUgcXTjFZGKGaQxJROhoOs96303226;     vMqBUgcXTjFZGKGaQxJROhoOs96303226 = vMqBUgcXTjFZGKGaQxJROhoOs47744873;     vMqBUgcXTjFZGKGaQxJROhoOs47744873 = vMqBUgcXTjFZGKGaQxJROhoOs83657233;     vMqBUgcXTjFZGKGaQxJROhoOs83657233 = vMqBUgcXTjFZGKGaQxJROhoOs12691121;     vMqBUgcXTjFZGKGaQxJROhoOs12691121 = vMqBUgcXTjFZGKGaQxJROhoOs68283565;     vMqBUgcXTjFZGKGaQxJROhoOs68283565 = vMqBUgcXTjFZGKGaQxJROhoOs40006883;     vMqBUgcXTjFZGKGaQxJROhoOs40006883 = vMqBUgcXTjFZGKGaQxJROhoOs19242844;     vMqBUgcXTjFZGKGaQxJROhoOs19242844 = vMqBUgcXTjFZGKGaQxJROhoOs94225531;     vMqBUgcXTjFZGKGaQxJROhoOs94225531 = vMqBUgcXTjFZGKGaQxJROhoOs1291167;     vMqBUgcXTjFZGKGaQxJROhoOs1291167 = vMqBUgcXTjFZGKGaQxJROhoOs2716621;     vMqBUgcXTjFZGKGaQxJROhoOs2716621 = vMqBUgcXTjFZGKGaQxJROhoOs71824563;     vMqBUgcXTjFZGKGaQxJROhoOs71824563 = vMqBUgcXTjFZGKGaQxJROhoOs84096238;     vMqBUgcXTjFZGKGaQxJROhoOs84096238 = vMqBUgcXTjFZGKGaQxJROhoOs90619974;     vMqBUgcXTjFZGKGaQxJROhoOs90619974 = vMqBUgcXTjFZGKGaQxJROhoOs61806415;     vMqBUgcXTjFZGKGaQxJROhoOs61806415 = vMqBUgcXTjFZGKGaQxJROhoOs92181139;     vMqBUgcXTjFZGKGaQxJROhoOs92181139 = vMqBUgcXTjFZGKGaQxJROhoOs26921018;     vMqBUgcXTjFZGKGaQxJROhoOs26921018 = vMqBUgcXTjFZGKGaQxJROhoOs3899183;     vMqBUgcXTjFZGKGaQxJROhoOs3899183 = vMqBUgcXTjFZGKGaQxJROhoOs17832461;     vMqBUgcXTjFZGKGaQxJROhoOs17832461 = vMqBUgcXTjFZGKGaQxJROhoOs40845442;     vMqBUgcXTjFZGKGaQxJROhoOs40845442 = vMqBUgcXTjFZGKGaQxJROhoOs75117930;     vMqBUgcXTjFZGKGaQxJROhoOs75117930 = vMqBUgcXTjFZGKGaQxJROhoOs63708568;     vMqBUgcXTjFZGKGaQxJROhoOs63708568 = vMqBUgcXTjFZGKGaQxJROhoOs86037834;     vMqBUgcXTjFZGKGaQxJROhoOs86037834 = vMqBUgcXTjFZGKGaQxJROhoOs43379353;     vMqBUgcXTjFZGKGaQxJROhoOs43379353 = vMqBUgcXTjFZGKGaQxJROhoOs79849857;     vMqBUgcXTjFZGKGaQxJROhoOs79849857 = vMqBUgcXTjFZGKGaQxJROhoOs66655272;     vMqBUgcXTjFZGKGaQxJROhoOs66655272 = vMqBUgcXTjFZGKGaQxJROhoOs84675240;     vMqBUgcXTjFZGKGaQxJROhoOs84675240 = vMqBUgcXTjFZGKGaQxJROhoOs25764745;     vMqBUgcXTjFZGKGaQxJROhoOs25764745 = vMqBUgcXTjFZGKGaQxJROhoOs844892;     vMqBUgcXTjFZGKGaQxJROhoOs844892 = vMqBUgcXTjFZGKGaQxJROhoOs497921;     vMqBUgcXTjFZGKGaQxJROhoOs497921 = vMqBUgcXTjFZGKGaQxJROhoOs86676461;     vMqBUgcXTjFZGKGaQxJROhoOs86676461 = vMqBUgcXTjFZGKGaQxJROhoOs9886909;     vMqBUgcXTjFZGKGaQxJROhoOs9886909 = vMqBUgcXTjFZGKGaQxJROhoOs96571883;     vMqBUgcXTjFZGKGaQxJROhoOs96571883 = vMqBUgcXTjFZGKGaQxJROhoOs21570895;     vMqBUgcXTjFZGKGaQxJROhoOs21570895 = vMqBUgcXTjFZGKGaQxJROhoOs26936217;     vMqBUgcXTjFZGKGaQxJROhoOs26936217 = vMqBUgcXTjFZGKGaQxJROhoOs61492708;     vMqBUgcXTjFZGKGaQxJROhoOs61492708 = vMqBUgcXTjFZGKGaQxJROhoOs46394235;     vMqBUgcXTjFZGKGaQxJROhoOs46394235 = vMqBUgcXTjFZGKGaQxJROhoOs17746374;     vMqBUgcXTjFZGKGaQxJROhoOs17746374 = vMqBUgcXTjFZGKGaQxJROhoOs26040386;     vMqBUgcXTjFZGKGaQxJROhoOs26040386 = vMqBUgcXTjFZGKGaQxJROhoOs69727999;     vMqBUgcXTjFZGKGaQxJROhoOs69727999 = vMqBUgcXTjFZGKGaQxJROhoOs64276013;     vMqBUgcXTjFZGKGaQxJROhoOs64276013 = vMqBUgcXTjFZGKGaQxJROhoOs26597746;     vMqBUgcXTjFZGKGaQxJROhoOs26597746 = vMqBUgcXTjFZGKGaQxJROhoOs69394118;     vMqBUgcXTjFZGKGaQxJROhoOs69394118 = vMqBUgcXTjFZGKGaQxJROhoOs59831147;     vMqBUgcXTjFZGKGaQxJROhoOs59831147 = vMqBUgcXTjFZGKGaQxJROhoOs93924983;     vMqBUgcXTjFZGKGaQxJROhoOs93924983 = vMqBUgcXTjFZGKGaQxJROhoOs33336747;     vMqBUgcXTjFZGKGaQxJROhoOs33336747 = vMqBUgcXTjFZGKGaQxJROhoOs72883959;     vMqBUgcXTjFZGKGaQxJROhoOs72883959 = vMqBUgcXTjFZGKGaQxJROhoOs89485426;     vMqBUgcXTjFZGKGaQxJROhoOs89485426 = vMqBUgcXTjFZGKGaQxJROhoOs28518395;     vMqBUgcXTjFZGKGaQxJROhoOs28518395 = vMqBUgcXTjFZGKGaQxJROhoOs71991430;     vMqBUgcXTjFZGKGaQxJROhoOs71991430 = vMqBUgcXTjFZGKGaQxJROhoOs31753191;     vMqBUgcXTjFZGKGaQxJROhoOs31753191 = vMqBUgcXTjFZGKGaQxJROhoOs21192815;     vMqBUgcXTjFZGKGaQxJROhoOs21192815 = vMqBUgcXTjFZGKGaQxJROhoOs69726001;     vMqBUgcXTjFZGKGaQxJROhoOs69726001 = vMqBUgcXTjFZGKGaQxJROhoOs74474306;     vMqBUgcXTjFZGKGaQxJROhoOs74474306 = vMqBUgcXTjFZGKGaQxJROhoOs24519981;     vMqBUgcXTjFZGKGaQxJROhoOs24519981 = vMqBUgcXTjFZGKGaQxJROhoOs40899035;     vMqBUgcXTjFZGKGaQxJROhoOs40899035 = vMqBUgcXTjFZGKGaQxJROhoOs10265393;     vMqBUgcXTjFZGKGaQxJROhoOs10265393 = vMqBUgcXTjFZGKGaQxJROhoOs4365520;     vMqBUgcXTjFZGKGaQxJROhoOs4365520 = vMqBUgcXTjFZGKGaQxJROhoOs3807376;     vMqBUgcXTjFZGKGaQxJROhoOs3807376 = vMqBUgcXTjFZGKGaQxJROhoOs46035848;     vMqBUgcXTjFZGKGaQxJROhoOs46035848 = vMqBUgcXTjFZGKGaQxJROhoOs83608325;     vMqBUgcXTjFZGKGaQxJROhoOs83608325 = vMqBUgcXTjFZGKGaQxJROhoOs14242138;     vMqBUgcXTjFZGKGaQxJROhoOs14242138 = vMqBUgcXTjFZGKGaQxJROhoOs18397952;     vMqBUgcXTjFZGKGaQxJROhoOs18397952 = vMqBUgcXTjFZGKGaQxJROhoOs93727610;     vMqBUgcXTjFZGKGaQxJROhoOs93727610 = vMqBUgcXTjFZGKGaQxJROhoOs14614706;     vMqBUgcXTjFZGKGaQxJROhoOs14614706 = vMqBUgcXTjFZGKGaQxJROhoOs92829711;     vMqBUgcXTjFZGKGaQxJROhoOs92829711 = vMqBUgcXTjFZGKGaQxJROhoOs75252679;     vMqBUgcXTjFZGKGaQxJROhoOs75252679 = vMqBUgcXTjFZGKGaQxJROhoOs62525344;     vMqBUgcXTjFZGKGaQxJROhoOs62525344 = vMqBUgcXTjFZGKGaQxJROhoOs63683758;     vMqBUgcXTjFZGKGaQxJROhoOs63683758 = vMqBUgcXTjFZGKGaQxJROhoOs313707;     vMqBUgcXTjFZGKGaQxJROhoOs313707 = vMqBUgcXTjFZGKGaQxJROhoOs45786904;     vMqBUgcXTjFZGKGaQxJROhoOs45786904 = vMqBUgcXTjFZGKGaQxJROhoOs9174644;     vMqBUgcXTjFZGKGaQxJROhoOs9174644 = vMqBUgcXTjFZGKGaQxJROhoOs77858797;     vMqBUgcXTjFZGKGaQxJROhoOs77858797 = vMqBUgcXTjFZGKGaQxJROhoOs48104461;     vMqBUgcXTjFZGKGaQxJROhoOs48104461 = vMqBUgcXTjFZGKGaQxJROhoOs76569429;     vMqBUgcXTjFZGKGaQxJROhoOs76569429 = vMqBUgcXTjFZGKGaQxJROhoOs48520185;     vMqBUgcXTjFZGKGaQxJROhoOs48520185 = vMqBUgcXTjFZGKGaQxJROhoOs97445370;}
// Junk Finished
