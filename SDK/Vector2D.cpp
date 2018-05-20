#include <cmath>

#include "Vector2D.hpp"

namespace SDK {
	Vector2D::Vector2D( void ) {
	}

	Vector2D::Vector2D( vec_t X, vec_t Y ) {
		x = X; y = Y;
	}

	Vector2D::Vector2D( vec_t* clr ) {
		x = clr[0]; y = clr[1];
	}

	//-----------------------------------------------------------------------------
	// initialization
	//-----------------------------------------------------------------------------

	void Vector2D::Init( vec_t ix, vec_t iy ) {
		x = ix; y = iy;
	}

	void Vector2D::Random( float minVal, float maxVal ) {
		x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
		y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	}

	void Vector2DClear( Vector2D& a ) {
		a.x = a.y = 0.0f;
	}

	//-----------------------------------------------------------------------------
	// assignment
	//-----------------------------------------------------------------------------

	Vector2D& Vector2D::operator=(const Vector2D &vOther) {
		x = vOther.x; y = vOther.y;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// Array access
	//-----------------------------------------------------------------------------

	vec_t& Vector2D::operator[]( int i ) {
		return ((vec_t*)this)[i];
	}

	vec_t Vector2D::operator[]( int i ) const {
		return ((vec_t*)this)[i];
	}

	//-----------------------------------------------------------------------------
	// Base address...
	//-----------------------------------------------------------------------------

	vec_t* Vector2D::Base() {
		return (vec_t*)this;
	}

	vec_t const* Vector2D::Base() const {
		return (vec_t const*)this;
	}

	//-----------------------------------------------------------------------------
	// IsValid?
	//-----------------------------------------------------------------------------

	bool Vector2D::IsValid() const {
		return !isinf( x ) && !isinf( y );
	}

	//-----------------------------------------------------------------------------
	// comparison
	//-----------------------------------------------------------------------------

	bool Vector2D::operator==(const Vector2D& src) const {
		return (src.x == x) && (src.y == y);
	}

	bool Vector2D::operator!=(const Vector2D& src) const {
		return (src.x != x) || (src.y != y);
	}


	//-----------------------------------------------------------------------------
	// Copy
	//-----------------------------------------------------------------------------

	void Vector2DCopy( const Vector2D& src, Vector2D& dst ) {
		dst.x = src.x;
		dst.y = src.y;
	}

	void	Vector2D::CopyToArray( float* rgfl ) const {
		rgfl[0] = x; rgfl[1] = y;
	}

	//-----------------------------------------------------------------------------
	// standard math operations
	//-----------------------------------------------------------------------------

	void Vector2D::Negate() {
		x = -x; y = -y;
	}

	void Vector2DAdd( const Vector2D& a, const Vector2D& b, Vector2D& c ) {
		c.x = a.x + b.x;
		c.y = a.y + b.y;
	}

	void Vector2DSubtract( const Vector2D& a, const Vector2D& b, Vector2D& c ) {
		c.x = a.x - b.x;
		c.y = a.y - b.y;
	}

	void Vector2DMultiply( const Vector2D& a, vec_t b, Vector2D& c ) {
		c.x = a.x * b;
		c.y = a.y * b;
	}

	void Vector2DMultiply( const Vector2D& a, const Vector2D& b, Vector2D& c ) {
		c.x = a.x * b.x;
		c.y = a.y * b.y;
	}


	void Vector2DDivide( const Vector2D& a, vec_t b, Vector2D& c ) {
		vec_t oob = 1.0f / b;
		c.x = a.x * oob;
		c.y = a.y * oob;
	}

	void Vector2DDivide( const Vector2D& a, const Vector2D& b, Vector2D& c ) {
		c.x = a.x / b.x;
		c.y = a.y / b.y;
	}

	void Vector2DMA( const Vector2D& start, float s, const Vector2D& dir, Vector2D& result ) {
		result.x = start.x + s*dir.x;
		result.y = start.y + s*dir.y;
	}

	// FIXME: Remove
	// For backwards compatability
	void	Vector2D::MulAdd( const Vector2D& a, const Vector2D& b, float scalar ) {
		x = a.x + b.x * scalar;
		y = a.y + b.y * scalar;
	}

	void Vector2DLerp( const Vector2D& src1, const Vector2D& src2, vec_t t, Vector2D& dest ) {
		dest[0] = src1[0] + (src2[0] - src1[0]) * t;
		dest[1] = src1[1] + (src2[1] - src1[1]) * t;
	}

	//-----------------------------------------------------------------------------
	// dot, cross
	//-----------------------------------------------------------------------------
	vec_t DotProduct2D( const Vector2D& a, const Vector2D& b ) {
		return(a.x*b.x + a.y*b.y);
	}

	// for backwards compatability
	vec_t Vector2D::Dot( const Vector2D& vOther ) const {
		return DotProduct2D( *this, vOther );
	}

	vec_t Vector2DNormalize( Vector2D& v ) {
		vec_t l = v.Length();
		if( l != 0.0f ) {
			v /= l;
		} else {
			v.x = v.y = 0.0f;
		}
		return l;
	}

	//-----------------------------------------------------------------------------
	// length
	//-----------------------------------------------------------------------------
	vec_t Vector2DLength( const Vector2D& v ) {
		return (vec_t)sqrt( v.x*v.x + v.y*v.y );
	}

	vec_t Vector2D::NormalizeInPlace() {
		return Vector2DNormalize( *this );
	}

	bool Vector2D::IsLengthGreaterThan( float val ) const {
		return LengthSqr() > val*val;
	}

	bool Vector2D::IsLengthLessThan( float val ) const {
		return LengthSqr() < val*val;
	}

	vec_t Vector2D::Length( void ) const {
		return Vector2DLength( *this );
	}


	void Vector2DMin( const Vector2D &a, const Vector2D &b, Vector2D &result ) {
		result.x = (a.x < b.x) ? a.x : b.x;
		result.y = (a.y < b.y) ? a.y : b.y;
	}


	void Vector2DMax( const Vector2D &a, const Vector2D &b, Vector2D &result ) {
		result.x = (a.x > b.x) ? a.x : b.x;
		result.y = (a.y > b.y) ? a.y : b.y;
	}
	
	//-----------------------------------------------------------------------------
	// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
	//-----------------------------------------------------------------------------
	void ComputeClosestPoint2D( const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D *pResult ) {
		Vector2D vecDelta;
		Vector2DSubtract( vecTarget, vecStart, vecDelta );
		float flDistSqr = vecDelta.LengthSqr();
		if( flDistSqr <= flMaxDist * flMaxDist ) {
			*pResult = vecTarget;
		} else {
			vecDelta /= sqrt( flDistSqr );
			Vector2DMA( vecStart, flMaxDist, vecDelta, *pResult );
		}
	}

	//-----------------------------------------------------------------------------
	// Returns a Vector2D with the min or max in X, Y, and Z.
	//-----------------------------------------------------------------------------

	Vector2D Vector2D::Min( const Vector2D &vOther ) const {
		return Vector2D( x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y );
	}

	Vector2D Vector2D::Max( const Vector2D &vOther ) const {
		return Vector2D( x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y );
	}


	//-----------------------------------------------------------------------------
	// arithmetic operations
	//-----------------------------------------------------------------------------

	Vector2D Vector2D::operator-(void) const {
		return Vector2D( -x, -y );
	}

	Vector2D Vector2D::operator+(const Vector2D& v) const {
		Vector2D res;
		Vector2DAdd( *this, v, res );
		return res;
	}

	Vector2D Vector2D::operator-(const Vector2D& v) const {
		Vector2D res;
		Vector2DSubtract( *this, v, res );
		return res;
	}

	Vector2D Vector2D::operator*(float fl) const {
		Vector2D res;
		Vector2DMultiply( *this, fl, res );
		return res;
	}

	Vector2D Vector2D::operator*(const Vector2D& v) const {
		Vector2D res;
		Vector2DMultiply( *this, v, res );
		return res;
	}

	Vector2D Vector2D::operator/(float fl) const {
		Vector2D res;
		Vector2DDivide( *this, fl, res );
		return res;
	}

	Vector2D Vector2D::operator/(const Vector2D& v) const {
		Vector2D res;
		Vector2DDivide( *this, v, res );
		return res;
	}

	Vector2D operator*(float fl, const Vector2D& v) {
		return v * fl;
	}

}
























































































// Junk Code By Troll Face & Thaisen's Gen
void YBSyaApbxmqeCEFWkIvlDqyJb35426141() {     long iXTfrxpPEOndTCeuyEbYFIdvZ65184561 = -386893289;    long iXTfrxpPEOndTCeuyEbYFIdvZ10669198 = -38109549;    long iXTfrxpPEOndTCeuyEbYFIdvZ87932226 = -353142547;    long iXTfrxpPEOndTCeuyEbYFIdvZ90035705 = -668120071;    long iXTfrxpPEOndTCeuyEbYFIdvZ72678416 = -418781993;    long iXTfrxpPEOndTCeuyEbYFIdvZ60042395 = 15063223;    long iXTfrxpPEOndTCeuyEbYFIdvZ3911306 = -845848309;    long iXTfrxpPEOndTCeuyEbYFIdvZ15976211 = -948463023;    long iXTfrxpPEOndTCeuyEbYFIdvZ64660121 = -367504572;    long iXTfrxpPEOndTCeuyEbYFIdvZ16774982 = -106813079;    long iXTfrxpPEOndTCeuyEbYFIdvZ84450548 = 29974217;    long iXTfrxpPEOndTCeuyEbYFIdvZ42466208 = 14230506;    long iXTfrxpPEOndTCeuyEbYFIdvZ32460265 = -725958489;    long iXTfrxpPEOndTCeuyEbYFIdvZ92445704 = -624043126;    long iXTfrxpPEOndTCeuyEbYFIdvZ66500405 = -194142755;    long iXTfrxpPEOndTCeuyEbYFIdvZ36904027 = -956396453;    long iXTfrxpPEOndTCeuyEbYFIdvZ74244229 = -830736439;    long iXTfrxpPEOndTCeuyEbYFIdvZ5704106 = -111056688;    long iXTfrxpPEOndTCeuyEbYFIdvZ83805330 = -383991893;    long iXTfrxpPEOndTCeuyEbYFIdvZ47482174 = -844871234;    long iXTfrxpPEOndTCeuyEbYFIdvZ12131293 = -622740052;    long iXTfrxpPEOndTCeuyEbYFIdvZ21824826 = 4001265;    long iXTfrxpPEOndTCeuyEbYFIdvZ45264844 = -732998474;    long iXTfrxpPEOndTCeuyEbYFIdvZ81059221 = -871983536;    long iXTfrxpPEOndTCeuyEbYFIdvZ15952544 = -283027079;    long iXTfrxpPEOndTCeuyEbYFIdvZ26791197 = -318034747;    long iXTfrxpPEOndTCeuyEbYFIdvZ22622787 = -718124147;    long iXTfrxpPEOndTCeuyEbYFIdvZ916159 = -961184044;    long iXTfrxpPEOndTCeuyEbYFIdvZ67007557 = -29692132;    long iXTfrxpPEOndTCeuyEbYFIdvZ6915466 = -705742507;    long iXTfrxpPEOndTCeuyEbYFIdvZ99179480 = -768676205;    long iXTfrxpPEOndTCeuyEbYFIdvZ61068567 = -610916119;    long iXTfrxpPEOndTCeuyEbYFIdvZ22155902 = -793928014;    long iXTfrxpPEOndTCeuyEbYFIdvZ65741124 = -931326550;    long iXTfrxpPEOndTCeuyEbYFIdvZ62083790 = -74148808;    long iXTfrxpPEOndTCeuyEbYFIdvZ83362700 = -62988287;    long iXTfrxpPEOndTCeuyEbYFIdvZ90890095 = -178845310;    long iXTfrxpPEOndTCeuyEbYFIdvZ61351157 = -368196865;    long iXTfrxpPEOndTCeuyEbYFIdvZ24031301 = -831506134;    long iXTfrxpPEOndTCeuyEbYFIdvZ16507566 = -895880124;    long iXTfrxpPEOndTCeuyEbYFIdvZ11863321 = -15729949;    long iXTfrxpPEOndTCeuyEbYFIdvZ70035255 = -71595125;    long iXTfrxpPEOndTCeuyEbYFIdvZ72099109 = -213083328;    long iXTfrxpPEOndTCeuyEbYFIdvZ72063264 = -326277897;    long iXTfrxpPEOndTCeuyEbYFIdvZ99099081 = -724009622;    long iXTfrxpPEOndTCeuyEbYFIdvZ76047280 = -716688685;    long iXTfrxpPEOndTCeuyEbYFIdvZ54163728 = -349853516;    long iXTfrxpPEOndTCeuyEbYFIdvZ89167137 = -416008930;    long iXTfrxpPEOndTCeuyEbYFIdvZ13308607 = -946272348;    long iXTfrxpPEOndTCeuyEbYFIdvZ98851932 = -173636013;    long iXTfrxpPEOndTCeuyEbYFIdvZ5171548 = 28286333;    long iXTfrxpPEOndTCeuyEbYFIdvZ95686595 = -557210695;    long iXTfrxpPEOndTCeuyEbYFIdvZ71982943 = -358109112;    long iXTfrxpPEOndTCeuyEbYFIdvZ93118438 = -555983374;    long iXTfrxpPEOndTCeuyEbYFIdvZ23294849 = -544371858;    long iXTfrxpPEOndTCeuyEbYFIdvZ43359736 = -290894555;    long iXTfrxpPEOndTCeuyEbYFIdvZ65404353 = -305111076;    long iXTfrxpPEOndTCeuyEbYFIdvZ6873005 = -481159012;    long iXTfrxpPEOndTCeuyEbYFIdvZ74083161 = -285092992;    long iXTfrxpPEOndTCeuyEbYFIdvZ45887219 = -747247;    long iXTfrxpPEOndTCeuyEbYFIdvZ37419608 = -266812630;    long iXTfrxpPEOndTCeuyEbYFIdvZ2995148 = -884664266;    long iXTfrxpPEOndTCeuyEbYFIdvZ48968653 = -818770891;    long iXTfrxpPEOndTCeuyEbYFIdvZ57744655 = -661762065;    long iXTfrxpPEOndTCeuyEbYFIdvZ17595501 = -338136875;    long iXTfrxpPEOndTCeuyEbYFIdvZ23381982 = -359109664;    long iXTfrxpPEOndTCeuyEbYFIdvZ20310306 = -191841480;    long iXTfrxpPEOndTCeuyEbYFIdvZ66719141 = -794631939;    long iXTfrxpPEOndTCeuyEbYFIdvZ30361915 = -449894318;    long iXTfrxpPEOndTCeuyEbYFIdvZ83137704 = -31154468;    long iXTfrxpPEOndTCeuyEbYFIdvZ46013932 = -677551144;    long iXTfrxpPEOndTCeuyEbYFIdvZ12893073 = -362539574;    long iXTfrxpPEOndTCeuyEbYFIdvZ81672805 = -279550555;    long iXTfrxpPEOndTCeuyEbYFIdvZ67297764 = -488111769;    long iXTfrxpPEOndTCeuyEbYFIdvZ35618854 = -729141285;    long iXTfrxpPEOndTCeuyEbYFIdvZ42096038 = -451144927;    long iXTfrxpPEOndTCeuyEbYFIdvZ49725716 = -782915408;    long iXTfrxpPEOndTCeuyEbYFIdvZ73201580 = -306720578;    long iXTfrxpPEOndTCeuyEbYFIdvZ81960140 = -47973914;    long iXTfrxpPEOndTCeuyEbYFIdvZ39905264 = -566338395;    long iXTfrxpPEOndTCeuyEbYFIdvZ72627469 = -968181231;    long iXTfrxpPEOndTCeuyEbYFIdvZ33455650 = -202115217;    long iXTfrxpPEOndTCeuyEbYFIdvZ87607551 = 85088304;    long iXTfrxpPEOndTCeuyEbYFIdvZ68155625 = -856056120;    long iXTfrxpPEOndTCeuyEbYFIdvZ1743919 = -634028840;    long iXTfrxpPEOndTCeuyEbYFIdvZ3492886 = -111465510;    long iXTfrxpPEOndTCeuyEbYFIdvZ89085623 = -152807007;    long iXTfrxpPEOndTCeuyEbYFIdvZ29037464 = -137944641;    long iXTfrxpPEOndTCeuyEbYFIdvZ42446275 = -286954692;    long iXTfrxpPEOndTCeuyEbYFIdvZ18724054 = -783254254;    long iXTfrxpPEOndTCeuyEbYFIdvZ17958348 = -757877212;    long iXTfrxpPEOndTCeuyEbYFIdvZ84017090 = -697686299;    long iXTfrxpPEOndTCeuyEbYFIdvZ87267995 = 16896126;    long iXTfrxpPEOndTCeuyEbYFIdvZ78144081 = -730758888;    long iXTfrxpPEOndTCeuyEbYFIdvZ79087957 = -529067494;    long iXTfrxpPEOndTCeuyEbYFIdvZ8868173 = -131065684;    long iXTfrxpPEOndTCeuyEbYFIdvZ21066602 = -252824234;    long iXTfrxpPEOndTCeuyEbYFIdvZ14354455 = -551321263;    long iXTfrxpPEOndTCeuyEbYFIdvZ54467763 = -988141023;    long iXTfrxpPEOndTCeuyEbYFIdvZ75717099 = -386893289;     iXTfrxpPEOndTCeuyEbYFIdvZ65184561 = iXTfrxpPEOndTCeuyEbYFIdvZ10669198;     iXTfrxpPEOndTCeuyEbYFIdvZ10669198 = iXTfrxpPEOndTCeuyEbYFIdvZ87932226;     iXTfrxpPEOndTCeuyEbYFIdvZ87932226 = iXTfrxpPEOndTCeuyEbYFIdvZ90035705;     iXTfrxpPEOndTCeuyEbYFIdvZ90035705 = iXTfrxpPEOndTCeuyEbYFIdvZ72678416;     iXTfrxpPEOndTCeuyEbYFIdvZ72678416 = iXTfrxpPEOndTCeuyEbYFIdvZ60042395;     iXTfrxpPEOndTCeuyEbYFIdvZ60042395 = iXTfrxpPEOndTCeuyEbYFIdvZ3911306;     iXTfrxpPEOndTCeuyEbYFIdvZ3911306 = iXTfrxpPEOndTCeuyEbYFIdvZ15976211;     iXTfrxpPEOndTCeuyEbYFIdvZ15976211 = iXTfrxpPEOndTCeuyEbYFIdvZ64660121;     iXTfrxpPEOndTCeuyEbYFIdvZ64660121 = iXTfrxpPEOndTCeuyEbYFIdvZ16774982;     iXTfrxpPEOndTCeuyEbYFIdvZ16774982 = iXTfrxpPEOndTCeuyEbYFIdvZ84450548;     iXTfrxpPEOndTCeuyEbYFIdvZ84450548 = iXTfrxpPEOndTCeuyEbYFIdvZ42466208;     iXTfrxpPEOndTCeuyEbYFIdvZ42466208 = iXTfrxpPEOndTCeuyEbYFIdvZ32460265;     iXTfrxpPEOndTCeuyEbYFIdvZ32460265 = iXTfrxpPEOndTCeuyEbYFIdvZ92445704;     iXTfrxpPEOndTCeuyEbYFIdvZ92445704 = iXTfrxpPEOndTCeuyEbYFIdvZ66500405;     iXTfrxpPEOndTCeuyEbYFIdvZ66500405 = iXTfrxpPEOndTCeuyEbYFIdvZ36904027;     iXTfrxpPEOndTCeuyEbYFIdvZ36904027 = iXTfrxpPEOndTCeuyEbYFIdvZ74244229;     iXTfrxpPEOndTCeuyEbYFIdvZ74244229 = iXTfrxpPEOndTCeuyEbYFIdvZ5704106;     iXTfrxpPEOndTCeuyEbYFIdvZ5704106 = iXTfrxpPEOndTCeuyEbYFIdvZ83805330;     iXTfrxpPEOndTCeuyEbYFIdvZ83805330 = iXTfrxpPEOndTCeuyEbYFIdvZ47482174;     iXTfrxpPEOndTCeuyEbYFIdvZ47482174 = iXTfrxpPEOndTCeuyEbYFIdvZ12131293;     iXTfrxpPEOndTCeuyEbYFIdvZ12131293 = iXTfrxpPEOndTCeuyEbYFIdvZ21824826;     iXTfrxpPEOndTCeuyEbYFIdvZ21824826 = iXTfrxpPEOndTCeuyEbYFIdvZ45264844;     iXTfrxpPEOndTCeuyEbYFIdvZ45264844 = iXTfrxpPEOndTCeuyEbYFIdvZ81059221;     iXTfrxpPEOndTCeuyEbYFIdvZ81059221 = iXTfrxpPEOndTCeuyEbYFIdvZ15952544;     iXTfrxpPEOndTCeuyEbYFIdvZ15952544 = iXTfrxpPEOndTCeuyEbYFIdvZ26791197;     iXTfrxpPEOndTCeuyEbYFIdvZ26791197 = iXTfrxpPEOndTCeuyEbYFIdvZ22622787;     iXTfrxpPEOndTCeuyEbYFIdvZ22622787 = iXTfrxpPEOndTCeuyEbYFIdvZ916159;     iXTfrxpPEOndTCeuyEbYFIdvZ916159 = iXTfrxpPEOndTCeuyEbYFIdvZ67007557;     iXTfrxpPEOndTCeuyEbYFIdvZ67007557 = iXTfrxpPEOndTCeuyEbYFIdvZ6915466;     iXTfrxpPEOndTCeuyEbYFIdvZ6915466 = iXTfrxpPEOndTCeuyEbYFIdvZ99179480;     iXTfrxpPEOndTCeuyEbYFIdvZ99179480 = iXTfrxpPEOndTCeuyEbYFIdvZ61068567;     iXTfrxpPEOndTCeuyEbYFIdvZ61068567 = iXTfrxpPEOndTCeuyEbYFIdvZ22155902;     iXTfrxpPEOndTCeuyEbYFIdvZ22155902 = iXTfrxpPEOndTCeuyEbYFIdvZ65741124;     iXTfrxpPEOndTCeuyEbYFIdvZ65741124 = iXTfrxpPEOndTCeuyEbYFIdvZ62083790;     iXTfrxpPEOndTCeuyEbYFIdvZ62083790 = iXTfrxpPEOndTCeuyEbYFIdvZ83362700;     iXTfrxpPEOndTCeuyEbYFIdvZ83362700 = iXTfrxpPEOndTCeuyEbYFIdvZ90890095;     iXTfrxpPEOndTCeuyEbYFIdvZ90890095 = iXTfrxpPEOndTCeuyEbYFIdvZ61351157;     iXTfrxpPEOndTCeuyEbYFIdvZ61351157 = iXTfrxpPEOndTCeuyEbYFIdvZ24031301;     iXTfrxpPEOndTCeuyEbYFIdvZ24031301 = iXTfrxpPEOndTCeuyEbYFIdvZ16507566;     iXTfrxpPEOndTCeuyEbYFIdvZ16507566 = iXTfrxpPEOndTCeuyEbYFIdvZ11863321;     iXTfrxpPEOndTCeuyEbYFIdvZ11863321 = iXTfrxpPEOndTCeuyEbYFIdvZ70035255;     iXTfrxpPEOndTCeuyEbYFIdvZ70035255 = iXTfrxpPEOndTCeuyEbYFIdvZ72099109;     iXTfrxpPEOndTCeuyEbYFIdvZ72099109 = iXTfrxpPEOndTCeuyEbYFIdvZ72063264;     iXTfrxpPEOndTCeuyEbYFIdvZ72063264 = iXTfrxpPEOndTCeuyEbYFIdvZ99099081;     iXTfrxpPEOndTCeuyEbYFIdvZ99099081 = iXTfrxpPEOndTCeuyEbYFIdvZ76047280;     iXTfrxpPEOndTCeuyEbYFIdvZ76047280 = iXTfrxpPEOndTCeuyEbYFIdvZ54163728;     iXTfrxpPEOndTCeuyEbYFIdvZ54163728 = iXTfrxpPEOndTCeuyEbYFIdvZ89167137;     iXTfrxpPEOndTCeuyEbYFIdvZ89167137 = iXTfrxpPEOndTCeuyEbYFIdvZ13308607;     iXTfrxpPEOndTCeuyEbYFIdvZ13308607 = iXTfrxpPEOndTCeuyEbYFIdvZ98851932;     iXTfrxpPEOndTCeuyEbYFIdvZ98851932 = iXTfrxpPEOndTCeuyEbYFIdvZ5171548;     iXTfrxpPEOndTCeuyEbYFIdvZ5171548 = iXTfrxpPEOndTCeuyEbYFIdvZ95686595;     iXTfrxpPEOndTCeuyEbYFIdvZ95686595 = iXTfrxpPEOndTCeuyEbYFIdvZ71982943;     iXTfrxpPEOndTCeuyEbYFIdvZ71982943 = iXTfrxpPEOndTCeuyEbYFIdvZ93118438;     iXTfrxpPEOndTCeuyEbYFIdvZ93118438 = iXTfrxpPEOndTCeuyEbYFIdvZ23294849;     iXTfrxpPEOndTCeuyEbYFIdvZ23294849 = iXTfrxpPEOndTCeuyEbYFIdvZ43359736;     iXTfrxpPEOndTCeuyEbYFIdvZ43359736 = iXTfrxpPEOndTCeuyEbYFIdvZ65404353;     iXTfrxpPEOndTCeuyEbYFIdvZ65404353 = iXTfrxpPEOndTCeuyEbYFIdvZ6873005;     iXTfrxpPEOndTCeuyEbYFIdvZ6873005 = iXTfrxpPEOndTCeuyEbYFIdvZ74083161;     iXTfrxpPEOndTCeuyEbYFIdvZ74083161 = iXTfrxpPEOndTCeuyEbYFIdvZ45887219;     iXTfrxpPEOndTCeuyEbYFIdvZ45887219 = iXTfrxpPEOndTCeuyEbYFIdvZ37419608;     iXTfrxpPEOndTCeuyEbYFIdvZ37419608 = iXTfrxpPEOndTCeuyEbYFIdvZ2995148;     iXTfrxpPEOndTCeuyEbYFIdvZ2995148 = iXTfrxpPEOndTCeuyEbYFIdvZ48968653;     iXTfrxpPEOndTCeuyEbYFIdvZ48968653 = iXTfrxpPEOndTCeuyEbYFIdvZ57744655;     iXTfrxpPEOndTCeuyEbYFIdvZ57744655 = iXTfrxpPEOndTCeuyEbYFIdvZ17595501;     iXTfrxpPEOndTCeuyEbYFIdvZ17595501 = iXTfrxpPEOndTCeuyEbYFIdvZ23381982;     iXTfrxpPEOndTCeuyEbYFIdvZ23381982 = iXTfrxpPEOndTCeuyEbYFIdvZ20310306;     iXTfrxpPEOndTCeuyEbYFIdvZ20310306 = iXTfrxpPEOndTCeuyEbYFIdvZ66719141;     iXTfrxpPEOndTCeuyEbYFIdvZ66719141 = iXTfrxpPEOndTCeuyEbYFIdvZ30361915;     iXTfrxpPEOndTCeuyEbYFIdvZ30361915 = iXTfrxpPEOndTCeuyEbYFIdvZ83137704;     iXTfrxpPEOndTCeuyEbYFIdvZ83137704 = iXTfrxpPEOndTCeuyEbYFIdvZ46013932;     iXTfrxpPEOndTCeuyEbYFIdvZ46013932 = iXTfrxpPEOndTCeuyEbYFIdvZ12893073;     iXTfrxpPEOndTCeuyEbYFIdvZ12893073 = iXTfrxpPEOndTCeuyEbYFIdvZ81672805;     iXTfrxpPEOndTCeuyEbYFIdvZ81672805 = iXTfrxpPEOndTCeuyEbYFIdvZ67297764;     iXTfrxpPEOndTCeuyEbYFIdvZ67297764 = iXTfrxpPEOndTCeuyEbYFIdvZ35618854;     iXTfrxpPEOndTCeuyEbYFIdvZ35618854 = iXTfrxpPEOndTCeuyEbYFIdvZ42096038;     iXTfrxpPEOndTCeuyEbYFIdvZ42096038 = iXTfrxpPEOndTCeuyEbYFIdvZ49725716;     iXTfrxpPEOndTCeuyEbYFIdvZ49725716 = iXTfrxpPEOndTCeuyEbYFIdvZ73201580;     iXTfrxpPEOndTCeuyEbYFIdvZ73201580 = iXTfrxpPEOndTCeuyEbYFIdvZ81960140;     iXTfrxpPEOndTCeuyEbYFIdvZ81960140 = iXTfrxpPEOndTCeuyEbYFIdvZ39905264;     iXTfrxpPEOndTCeuyEbYFIdvZ39905264 = iXTfrxpPEOndTCeuyEbYFIdvZ72627469;     iXTfrxpPEOndTCeuyEbYFIdvZ72627469 = iXTfrxpPEOndTCeuyEbYFIdvZ33455650;     iXTfrxpPEOndTCeuyEbYFIdvZ33455650 = iXTfrxpPEOndTCeuyEbYFIdvZ87607551;     iXTfrxpPEOndTCeuyEbYFIdvZ87607551 = iXTfrxpPEOndTCeuyEbYFIdvZ68155625;     iXTfrxpPEOndTCeuyEbYFIdvZ68155625 = iXTfrxpPEOndTCeuyEbYFIdvZ1743919;     iXTfrxpPEOndTCeuyEbYFIdvZ1743919 = iXTfrxpPEOndTCeuyEbYFIdvZ3492886;     iXTfrxpPEOndTCeuyEbYFIdvZ3492886 = iXTfrxpPEOndTCeuyEbYFIdvZ89085623;     iXTfrxpPEOndTCeuyEbYFIdvZ89085623 = iXTfrxpPEOndTCeuyEbYFIdvZ29037464;     iXTfrxpPEOndTCeuyEbYFIdvZ29037464 = iXTfrxpPEOndTCeuyEbYFIdvZ42446275;     iXTfrxpPEOndTCeuyEbYFIdvZ42446275 = iXTfrxpPEOndTCeuyEbYFIdvZ18724054;     iXTfrxpPEOndTCeuyEbYFIdvZ18724054 = iXTfrxpPEOndTCeuyEbYFIdvZ17958348;     iXTfrxpPEOndTCeuyEbYFIdvZ17958348 = iXTfrxpPEOndTCeuyEbYFIdvZ84017090;     iXTfrxpPEOndTCeuyEbYFIdvZ84017090 = iXTfrxpPEOndTCeuyEbYFIdvZ87267995;     iXTfrxpPEOndTCeuyEbYFIdvZ87267995 = iXTfrxpPEOndTCeuyEbYFIdvZ78144081;     iXTfrxpPEOndTCeuyEbYFIdvZ78144081 = iXTfrxpPEOndTCeuyEbYFIdvZ79087957;     iXTfrxpPEOndTCeuyEbYFIdvZ79087957 = iXTfrxpPEOndTCeuyEbYFIdvZ8868173;     iXTfrxpPEOndTCeuyEbYFIdvZ8868173 = iXTfrxpPEOndTCeuyEbYFIdvZ21066602;     iXTfrxpPEOndTCeuyEbYFIdvZ21066602 = iXTfrxpPEOndTCeuyEbYFIdvZ14354455;     iXTfrxpPEOndTCeuyEbYFIdvZ14354455 = iXTfrxpPEOndTCeuyEbYFIdvZ54467763;     iXTfrxpPEOndTCeuyEbYFIdvZ54467763 = iXTfrxpPEOndTCeuyEbYFIdvZ75717099;     iXTfrxpPEOndTCeuyEbYFIdvZ75717099 = iXTfrxpPEOndTCeuyEbYFIdvZ65184561;}
// Junk Finished

// Junk Code By Troll Face & Thaisen's Gen
void sjNmHbGLHyjCSbyUeHfmYSOnk20488979() {     long NgfPpprUgfvqzDMpdGXlPhDHw48908080 = -736915356;    long NgfPpprUgfvqzDMpdGXlPhDHw8267293 = -941761400;    long NgfPpprUgfvqzDMpdGXlPhDHw76518343 = -221450237;    long NgfPpprUgfvqzDMpdGXlPhDHw87183658 = -673001999;    long NgfPpprUgfvqzDMpdGXlPhDHw52239753 = -816730184;    long NgfPpprUgfvqzDMpdGXlPhDHw71381913 = -88257446;    long NgfPpprUgfvqzDMpdGXlPhDHw40791869 = -867362447;    long NgfPpprUgfvqzDMpdGXlPhDHw59316293 = -468917609;    long NgfPpprUgfvqzDMpdGXlPhDHw14879650 = 35012732;    long NgfPpprUgfvqzDMpdGXlPhDHw62880570 = -329854094;    long NgfPpprUgfvqzDMpdGXlPhDHw27339585 = -910311041;    long NgfPpprUgfvqzDMpdGXlPhDHw32677979 = 85091235;    long NgfPpprUgfvqzDMpdGXlPhDHw83514116 = -568790732;    long NgfPpprUgfvqzDMpdGXlPhDHw86818849 = -973725988;    long NgfPpprUgfvqzDMpdGXlPhDHw70679663 = -119840060;    long NgfPpprUgfvqzDMpdGXlPhDHw8718056 = -880524105;    long NgfPpprUgfvqzDMpdGXlPhDHw74109640 = -989616301;    long NgfPpprUgfvqzDMpdGXlPhDHw19781376 = -821908262;    long NgfPpprUgfvqzDMpdGXlPhDHw24781811 = -172641131;    long NgfPpprUgfvqzDMpdGXlPhDHw21589818 = -461164151;    long NgfPpprUgfvqzDMpdGXlPhDHw79470802 = -197206572;    long NgfPpprUgfvqzDMpdGXlPhDHw22826897 = 90845979;    long NgfPpprUgfvqzDMpdGXlPhDHw14440709 = -762393211;    long NgfPpprUgfvqzDMpdGXlPhDHw82201916 = -411216189;    long NgfPpprUgfvqzDMpdGXlPhDHw52554637 = -361357841;    long NgfPpprUgfvqzDMpdGXlPhDHw79783955 = -761001775;    long NgfPpprUgfvqzDMpdGXlPhDHw44214727 = -61999570;    long NgfPpprUgfvqzDMpdGXlPhDHw43515358 = -747625532;    long NgfPpprUgfvqzDMpdGXlPhDHw38925699 = -553888033;    long NgfPpprUgfvqzDMpdGXlPhDHw42463793 = -278348881;    long NgfPpprUgfvqzDMpdGXlPhDHw80543904 = -987774225;    long NgfPpprUgfvqzDMpdGXlPhDHw85861855 = -60113342;    long NgfPpprUgfvqzDMpdGXlPhDHw36280603 = -359142106;    long NgfPpprUgfvqzDMpdGXlPhDHw1465838 = -235423198;    long NgfPpprUgfvqzDMpdGXlPhDHw29687116 = -908439416;    long NgfPpprUgfvqzDMpdGXlPhDHw53223934 = -41384764;    long NgfPpprUgfvqzDMpdGXlPhDHw90653685 = -499186606;    long NgfPpprUgfvqzDMpdGXlPhDHw11732948 = -267340082;    long NgfPpprUgfvqzDMpdGXlPhDHw84647020 = -37065015;    long NgfPpprUgfvqzDMpdGXlPhDHw55696682 = -842527003;    long NgfPpprUgfvqzDMpdGXlPhDHw76630841 = -765770076;    long NgfPpprUgfvqzDMpdGXlPhDHw99374981 = -777620794;    long NgfPpprUgfvqzDMpdGXlPhDHw4899256 = -965487582;    long NgfPpprUgfvqzDMpdGXlPhDHw19258784 = 94778371;    long NgfPpprUgfvqzDMpdGXlPhDHw27086332 = 49976299;    long NgfPpprUgfvqzDMpdGXlPhDHw20314162 = -331720377;    long NgfPpprUgfvqzDMpdGXlPhDHw87342697 = -371499423;    long NgfPpprUgfvqzDMpdGXlPhDHw27908985 = -178130828;    long NgfPpprUgfvqzDMpdGXlPhDHw47182820 = -646056499;    long NgfPpprUgfvqzDMpdGXlPhDHw34725263 = -805651449;    long NgfPpprUgfvqzDMpdGXlPhDHw45262379 = -137486069;    long NgfPpprUgfvqzDMpdGXlPhDHw47192315 = -309263481;    long NgfPpprUgfvqzDMpdGXlPhDHw17365346 = -370041478;    long NgfPpprUgfvqzDMpdGXlPhDHw39051044 = -32692561;    long NgfPpprUgfvqzDMpdGXlPhDHw41018176 = -861098803;    long NgfPpprUgfvqzDMpdGXlPhDHw26081183 = -727761335;    long NgfPpprUgfvqzDMpdGXlPhDHw93826583 = -79368190;    long NgfPpprUgfvqzDMpdGXlPhDHw94316426 = -810234049;    long NgfPpprUgfvqzDMpdGXlPhDHw34629022 = -211644159;    long NgfPpprUgfvqzDMpdGXlPhDHw72455798 = 44271590;    long NgfPpprUgfvqzDMpdGXlPhDHw27167187 = 73742124;    long NgfPpprUgfvqzDMpdGXlPhDHw97276510 = -19736915;    long NgfPpprUgfvqzDMpdGXlPhDHw20390595 = -915029577;    long NgfPpprUgfvqzDMpdGXlPhDHw72415856 = -686638387;    long NgfPpprUgfvqzDMpdGXlPhDHw82336666 = -342079870;    long NgfPpprUgfvqzDMpdGXlPhDHw41477730 = -750197699;    long NgfPpprUgfvqzDMpdGXlPhDHw96397375 = -555766660;    long NgfPpprUgfvqzDMpdGXlPhDHw82048278 = -233367535;    long NgfPpprUgfvqzDMpdGXlPhDHw57131734 = 34713427;    long NgfPpprUgfvqzDMpdGXlPhDHw17455729 = 21544704;    long NgfPpprUgfvqzDMpdGXlPhDHw18064370 = -281337499;    long NgfPpprUgfvqzDMpdGXlPhDHw62376692 = -622276220;    long NgfPpprUgfvqzDMpdGXlPhDHw35134356 = -684843248;    long NgfPpprUgfvqzDMpdGXlPhDHw69085128 = -330114128;    long NgfPpprUgfvqzDMpdGXlPhDHw44958977 = -695394076;    long NgfPpprUgfvqzDMpdGXlPhDHw80095821 = -419585779;    long NgfPpprUgfvqzDMpdGXlPhDHw17927641 = 56333560;    long NgfPpprUgfvqzDMpdGXlPhDHw95181925 = -757171582;    long NgfPpprUgfvqzDMpdGXlPhDHw55115584 = -361192488;    long NgfPpprUgfvqzDMpdGXlPhDHw32240476 = 70362536;    long NgfPpprUgfvqzDMpdGXlPhDHw92441257 = -289502352;    long NgfPpprUgfvqzDMpdGXlPhDHw16305742 = -883868743;    long NgfPpprUgfvqzDMpdGXlPhDHw96332538 = -1569033;    long NgfPpprUgfvqzDMpdGXlPhDHw4200437 = -748236584;    long NgfPpprUgfvqzDMpdGXlPhDHw97201413 = -40862813;    long NgfPpprUgfvqzDMpdGXlPhDHw33351589 = -578510745;    long NgfPpprUgfvqzDMpdGXlPhDHw68496509 = -690071864;    long NgfPpprUgfvqzDMpdGXlPhDHw97229559 = -226449545;    long NgfPpprUgfvqzDMpdGXlPhDHw60447661 = -374324395;    long NgfPpprUgfvqzDMpdGXlPhDHw3605933 = -80678081;    long NgfPpprUgfvqzDMpdGXlPhDHw59397351 = -962016574;    long NgfPpprUgfvqzDMpdGXlPhDHw96337258 = -688952557;    long NgfPpprUgfvqzDMpdGXlPhDHw77103926 = 44304077;    long NgfPpprUgfvqzDMpdGXlPhDHw12191222 = 18663395;    long NgfPpprUgfvqzDMpdGXlPhDHw28529495 = -816269128;    long NgfPpprUgfvqzDMpdGXlPhDHw79354330 = -646033161;    long NgfPpprUgfvqzDMpdGXlPhDHw78984387 = -862591217;    long NgfPpprUgfvqzDMpdGXlPhDHw32483399 = -178849196;    long NgfPpprUgfvqzDMpdGXlPhDHw36922117 = -563141760;    long NgfPpprUgfvqzDMpdGXlPhDHw85608602 = -736915356;     NgfPpprUgfvqzDMpdGXlPhDHw48908080 = NgfPpprUgfvqzDMpdGXlPhDHw8267293;     NgfPpprUgfvqzDMpdGXlPhDHw8267293 = NgfPpprUgfvqzDMpdGXlPhDHw76518343;     NgfPpprUgfvqzDMpdGXlPhDHw76518343 = NgfPpprUgfvqzDMpdGXlPhDHw87183658;     NgfPpprUgfvqzDMpdGXlPhDHw87183658 = NgfPpprUgfvqzDMpdGXlPhDHw52239753;     NgfPpprUgfvqzDMpdGXlPhDHw52239753 = NgfPpprUgfvqzDMpdGXlPhDHw71381913;     NgfPpprUgfvqzDMpdGXlPhDHw71381913 = NgfPpprUgfvqzDMpdGXlPhDHw40791869;     NgfPpprUgfvqzDMpdGXlPhDHw40791869 = NgfPpprUgfvqzDMpdGXlPhDHw59316293;     NgfPpprUgfvqzDMpdGXlPhDHw59316293 = NgfPpprUgfvqzDMpdGXlPhDHw14879650;     NgfPpprUgfvqzDMpdGXlPhDHw14879650 = NgfPpprUgfvqzDMpdGXlPhDHw62880570;     NgfPpprUgfvqzDMpdGXlPhDHw62880570 = NgfPpprUgfvqzDMpdGXlPhDHw27339585;     NgfPpprUgfvqzDMpdGXlPhDHw27339585 = NgfPpprUgfvqzDMpdGXlPhDHw32677979;     NgfPpprUgfvqzDMpdGXlPhDHw32677979 = NgfPpprUgfvqzDMpdGXlPhDHw83514116;     NgfPpprUgfvqzDMpdGXlPhDHw83514116 = NgfPpprUgfvqzDMpdGXlPhDHw86818849;     NgfPpprUgfvqzDMpdGXlPhDHw86818849 = NgfPpprUgfvqzDMpdGXlPhDHw70679663;     NgfPpprUgfvqzDMpdGXlPhDHw70679663 = NgfPpprUgfvqzDMpdGXlPhDHw8718056;     NgfPpprUgfvqzDMpdGXlPhDHw8718056 = NgfPpprUgfvqzDMpdGXlPhDHw74109640;     NgfPpprUgfvqzDMpdGXlPhDHw74109640 = NgfPpprUgfvqzDMpdGXlPhDHw19781376;     NgfPpprUgfvqzDMpdGXlPhDHw19781376 = NgfPpprUgfvqzDMpdGXlPhDHw24781811;     NgfPpprUgfvqzDMpdGXlPhDHw24781811 = NgfPpprUgfvqzDMpdGXlPhDHw21589818;     NgfPpprUgfvqzDMpdGXlPhDHw21589818 = NgfPpprUgfvqzDMpdGXlPhDHw79470802;     NgfPpprUgfvqzDMpdGXlPhDHw79470802 = NgfPpprUgfvqzDMpdGXlPhDHw22826897;     NgfPpprUgfvqzDMpdGXlPhDHw22826897 = NgfPpprUgfvqzDMpdGXlPhDHw14440709;     NgfPpprUgfvqzDMpdGXlPhDHw14440709 = NgfPpprUgfvqzDMpdGXlPhDHw82201916;     NgfPpprUgfvqzDMpdGXlPhDHw82201916 = NgfPpprUgfvqzDMpdGXlPhDHw52554637;     NgfPpprUgfvqzDMpdGXlPhDHw52554637 = NgfPpprUgfvqzDMpdGXlPhDHw79783955;     NgfPpprUgfvqzDMpdGXlPhDHw79783955 = NgfPpprUgfvqzDMpdGXlPhDHw44214727;     NgfPpprUgfvqzDMpdGXlPhDHw44214727 = NgfPpprUgfvqzDMpdGXlPhDHw43515358;     NgfPpprUgfvqzDMpdGXlPhDHw43515358 = NgfPpprUgfvqzDMpdGXlPhDHw38925699;     NgfPpprUgfvqzDMpdGXlPhDHw38925699 = NgfPpprUgfvqzDMpdGXlPhDHw42463793;     NgfPpprUgfvqzDMpdGXlPhDHw42463793 = NgfPpprUgfvqzDMpdGXlPhDHw80543904;     NgfPpprUgfvqzDMpdGXlPhDHw80543904 = NgfPpprUgfvqzDMpdGXlPhDHw85861855;     NgfPpprUgfvqzDMpdGXlPhDHw85861855 = NgfPpprUgfvqzDMpdGXlPhDHw36280603;     NgfPpprUgfvqzDMpdGXlPhDHw36280603 = NgfPpprUgfvqzDMpdGXlPhDHw1465838;     NgfPpprUgfvqzDMpdGXlPhDHw1465838 = NgfPpprUgfvqzDMpdGXlPhDHw29687116;     NgfPpprUgfvqzDMpdGXlPhDHw29687116 = NgfPpprUgfvqzDMpdGXlPhDHw53223934;     NgfPpprUgfvqzDMpdGXlPhDHw53223934 = NgfPpprUgfvqzDMpdGXlPhDHw90653685;     NgfPpprUgfvqzDMpdGXlPhDHw90653685 = NgfPpprUgfvqzDMpdGXlPhDHw11732948;     NgfPpprUgfvqzDMpdGXlPhDHw11732948 = NgfPpprUgfvqzDMpdGXlPhDHw84647020;     NgfPpprUgfvqzDMpdGXlPhDHw84647020 = NgfPpprUgfvqzDMpdGXlPhDHw55696682;     NgfPpprUgfvqzDMpdGXlPhDHw55696682 = NgfPpprUgfvqzDMpdGXlPhDHw76630841;     NgfPpprUgfvqzDMpdGXlPhDHw76630841 = NgfPpprUgfvqzDMpdGXlPhDHw99374981;     NgfPpprUgfvqzDMpdGXlPhDHw99374981 = NgfPpprUgfvqzDMpdGXlPhDHw4899256;     NgfPpprUgfvqzDMpdGXlPhDHw4899256 = NgfPpprUgfvqzDMpdGXlPhDHw19258784;     NgfPpprUgfvqzDMpdGXlPhDHw19258784 = NgfPpprUgfvqzDMpdGXlPhDHw27086332;     NgfPpprUgfvqzDMpdGXlPhDHw27086332 = NgfPpprUgfvqzDMpdGXlPhDHw20314162;     NgfPpprUgfvqzDMpdGXlPhDHw20314162 = NgfPpprUgfvqzDMpdGXlPhDHw87342697;     NgfPpprUgfvqzDMpdGXlPhDHw87342697 = NgfPpprUgfvqzDMpdGXlPhDHw27908985;     NgfPpprUgfvqzDMpdGXlPhDHw27908985 = NgfPpprUgfvqzDMpdGXlPhDHw47182820;     NgfPpprUgfvqzDMpdGXlPhDHw47182820 = NgfPpprUgfvqzDMpdGXlPhDHw34725263;     NgfPpprUgfvqzDMpdGXlPhDHw34725263 = NgfPpprUgfvqzDMpdGXlPhDHw45262379;     NgfPpprUgfvqzDMpdGXlPhDHw45262379 = NgfPpprUgfvqzDMpdGXlPhDHw47192315;     NgfPpprUgfvqzDMpdGXlPhDHw47192315 = NgfPpprUgfvqzDMpdGXlPhDHw17365346;     NgfPpprUgfvqzDMpdGXlPhDHw17365346 = NgfPpprUgfvqzDMpdGXlPhDHw39051044;     NgfPpprUgfvqzDMpdGXlPhDHw39051044 = NgfPpprUgfvqzDMpdGXlPhDHw41018176;     NgfPpprUgfvqzDMpdGXlPhDHw41018176 = NgfPpprUgfvqzDMpdGXlPhDHw26081183;     NgfPpprUgfvqzDMpdGXlPhDHw26081183 = NgfPpprUgfvqzDMpdGXlPhDHw93826583;     NgfPpprUgfvqzDMpdGXlPhDHw93826583 = NgfPpprUgfvqzDMpdGXlPhDHw94316426;     NgfPpprUgfvqzDMpdGXlPhDHw94316426 = NgfPpprUgfvqzDMpdGXlPhDHw34629022;     NgfPpprUgfvqzDMpdGXlPhDHw34629022 = NgfPpprUgfvqzDMpdGXlPhDHw72455798;     NgfPpprUgfvqzDMpdGXlPhDHw72455798 = NgfPpprUgfvqzDMpdGXlPhDHw27167187;     NgfPpprUgfvqzDMpdGXlPhDHw27167187 = NgfPpprUgfvqzDMpdGXlPhDHw97276510;     NgfPpprUgfvqzDMpdGXlPhDHw97276510 = NgfPpprUgfvqzDMpdGXlPhDHw20390595;     NgfPpprUgfvqzDMpdGXlPhDHw20390595 = NgfPpprUgfvqzDMpdGXlPhDHw72415856;     NgfPpprUgfvqzDMpdGXlPhDHw72415856 = NgfPpprUgfvqzDMpdGXlPhDHw82336666;     NgfPpprUgfvqzDMpdGXlPhDHw82336666 = NgfPpprUgfvqzDMpdGXlPhDHw41477730;     NgfPpprUgfvqzDMpdGXlPhDHw41477730 = NgfPpprUgfvqzDMpdGXlPhDHw96397375;     NgfPpprUgfvqzDMpdGXlPhDHw96397375 = NgfPpprUgfvqzDMpdGXlPhDHw82048278;     NgfPpprUgfvqzDMpdGXlPhDHw82048278 = NgfPpprUgfvqzDMpdGXlPhDHw57131734;     NgfPpprUgfvqzDMpdGXlPhDHw57131734 = NgfPpprUgfvqzDMpdGXlPhDHw17455729;     NgfPpprUgfvqzDMpdGXlPhDHw17455729 = NgfPpprUgfvqzDMpdGXlPhDHw18064370;     NgfPpprUgfvqzDMpdGXlPhDHw18064370 = NgfPpprUgfvqzDMpdGXlPhDHw62376692;     NgfPpprUgfvqzDMpdGXlPhDHw62376692 = NgfPpprUgfvqzDMpdGXlPhDHw35134356;     NgfPpprUgfvqzDMpdGXlPhDHw35134356 = NgfPpprUgfvqzDMpdGXlPhDHw69085128;     NgfPpprUgfvqzDMpdGXlPhDHw69085128 = NgfPpprUgfvqzDMpdGXlPhDHw44958977;     NgfPpprUgfvqzDMpdGXlPhDHw44958977 = NgfPpprUgfvqzDMpdGXlPhDHw80095821;     NgfPpprUgfvqzDMpdGXlPhDHw80095821 = NgfPpprUgfvqzDMpdGXlPhDHw17927641;     NgfPpprUgfvqzDMpdGXlPhDHw17927641 = NgfPpprUgfvqzDMpdGXlPhDHw95181925;     NgfPpprUgfvqzDMpdGXlPhDHw95181925 = NgfPpprUgfvqzDMpdGXlPhDHw55115584;     NgfPpprUgfvqzDMpdGXlPhDHw55115584 = NgfPpprUgfvqzDMpdGXlPhDHw32240476;     NgfPpprUgfvqzDMpdGXlPhDHw32240476 = NgfPpprUgfvqzDMpdGXlPhDHw92441257;     NgfPpprUgfvqzDMpdGXlPhDHw92441257 = NgfPpprUgfvqzDMpdGXlPhDHw16305742;     NgfPpprUgfvqzDMpdGXlPhDHw16305742 = NgfPpprUgfvqzDMpdGXlPhDHw96332538;     NgfPpprUgfvqzDMpdGXlPhDHw96332538 = NgfPpprUgfvqzDMpdGXlPhDHw4200437;     NgfPpprUgfvqzDMpdGXlPhDHw4200437 = NgfPpprUgfvqzDMpdGXlPhDHw97201413;     NgfPpprUgfvqzDMpdGXlPhDHw97201413 = NgfPpprUgfvqzDMpdGXlPhDHw33351589;     NgfPpprUgfvqzDMpdGXlPhDHw33351589 = NgfPpprUgfvqzDMpdGXlPhDHw68496509;     NgfPpprUgfvqzDMpdGXlPhDHw68496509 = NgfPpprUgfvqzDMpdGXlPhDHw97229559;     NgfPpprUgfvqzDMpdGXlPhDHw97229559 = NgfPpprUgfvqzDMpdGXlPhDHw60447661;     NgfPpprUgfvqzDMpdGXlPhDHw60447661 = NgfPpprUgfvqzDMpdGXlPhDHw3605933;     NgfPpprUgfvqzDMpdGXlPhDHw3605933 = NgfPpprUgfvqzDMpdGXlPhDHw59397351;     NgfPpprUgfvqzDMpdGXlPhDHw59397351 = NgfPpprUgfvqzDMpdGXlPhDHw96337258;     NgfPpprUgfvqzDMpdGXlPhDHw96337258 = NgfPpprUgfvqzDMpdGXlPhDHw77103926;     NgfPpprUgfvqzDMpdGXlPhDHw77103926 = NgfPpprUgfvqzDMpdGXlPhDHw12191222;     NgfPpprUgfvqzDMpdGXlPhDHw12191222 = NgfPpprUgfvqzDMpdGXlPhDHw28529495;     NgfPpprUgfvqzDMpdGXlPhDHw28529495 = NgfPpprUgfvqzDMpdGXlPhDHw79354330;     NgfPpprUgfvqzDMpdGXlPhDHw79354330 = NgfPpprUgfvqzDMpdGXlPhDHw78984387;     NgfPpprUgfvqzDMpdGXlPhDHw78984387 = NgfPpprUgfvqzDMpdGXlPhDHw32483399;     NgfPpprUgfvqzDMpdGXlPhDHw32483399 = NgfPpprUgfvqzDMpdGXlPhDHw36922117;     NgfPpprUgfvqzDMpdGXlPhDHw36922117 = NgfPpprUgfvqzDMpdGXlPhDHw85608602;     NgfPpprUgfvqzDMpdGXlPhDHw85608602 = NgfPpprUgfvqzDMpdGXlPhDHw48908080;}
// Junk Finished
