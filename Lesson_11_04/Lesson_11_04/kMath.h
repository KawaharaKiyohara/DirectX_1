/*!
 * @brief	数学関係色々。
 */

#pragma once


class CMath{
public:
	static const float PI;
	/*!
	 * @brief	degreeからradianに変換。
	 */
	static float DegToRad( float deg )
	{
		return deg * (PI/180.0f);
	}
	/*!
	 * @brief	radianからdegreeに変換。
	 */
	static float RadToDeg( float rad )
	{
		return rad / (PI/180.0f);
	}
	/*!
	 *@brief	t0とt1間を線形補完。
	 *@details
	 *  ret = t0 + (t1-t0) + rate;
	 *@param[in]	t		補間率	0.0〜1.0
	 */
	static inline float Lerp(float rate, float t0, float t1)
	{
		return t0 + (t1 - t0)*rate;
	}
};
