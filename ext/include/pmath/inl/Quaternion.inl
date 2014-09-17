#include "../Quaternion.hpp"
#include "../Util.hpp"
#include "../Trigonometry.hpp"

namespace pmath
{
    template<typename T>
    const Quaternion<T> Quaternion<T>::identity = Quaternion<T>();

    template<typename T>
    inline Quaternion<T>::Quaternion()
        : w(T(1))
    { }

    template<typename T>
    inline Quaternion<T>::Quaternion(const T& w, const T& x, const T& y, const T& z)
        : w(w),
          vector(x, y, z)
    { }

    template<typename T>
    inline Quaternion<T>::Quaternion(const T& w, const Vector3<T>& vector)
        : w(w),
          vector(vector)
    { }

    template<typename T>
    inline Quaternion<T>::Quaternion(const Quaternion<T>& quaternion)
        : w(quaternion.w),
          vector(quaternion.vector)
    { }

    template<typename T>
    template<typename T2>
    inline Quaternion<T>::Quaternion(const Quaternion<T2>& quaternion)
        : w(static_cast<T>(quaternion.w)),
          vector(quaternion.vector)
    { }

    template<typename T>
    inline Quaternion<T>::Quaternion(const Matrix3<T>& matrix)
    {
        if(matrix[0][0] + matrix[1][1] + matrix[2][2] > 0)
        {
            const T t = matrix[0][0] + matrix[1][1] + matrix[2][2] + 1;
            const T s = 1 / sqrt(t) * T(0.5);

            w        = s * t;
            vector.x = (matrix[2][1] - matrix[1][2]) * s;
		    vector.y = (matrix[0][2] - matrix[2][0]) * s;
		    vector.z = (matrix[1][0] - matrix[0][1]) * s;
        }
        else if( matrix[0][0] > matrix[1][1] && matrix[0][0] > matrix[2][2])
        {
            const T t = matrix[0][0] - matrix[1][1] - matrix[2][2] + 1;
            const T s = 1 / sqrt(t) * T(0.5);

            w        = (matrix[2][1] - matrix[1][2]) * s;
            vector.x = s * t;
		    vector.y = (matrix[1][0] + matrix[0][1]) * s;
		    vector.z = (matrix[0][2] + matrix[2][0]) * s;
        }
        else if(matrix[1][1] > matrix[2][2])
        {
            const T t = -matrix[0][0] + matrix[1][1] - matrix[2][2] + 1;
            const T s = 1 / sqrt(t) * T(0.5);

            w        = (matrix[0][2] - matrix[2][0]) * s;
            vector.x = (matrix[1][0] + matrix[0][1]) * s;
		    vector.y = s * t;
		    vector.z = (matrix[2][1] + matrix[1][2]) * s;
        }
        else
        {
            const T t = -matrix[0][0] - matrix[1][1] + matrix[2][2] + 1;
            const T s = 1 / sqrt(t) * T(0.5);

            w        = (matrix[1][0] - matrix[0][1]) * s;
            vector.x = (matrix[0][2] + matrix[2][0]) * s;
		    vector.y = (matrix[2][1] + matrix[1][2]) * s;
		    vector.z = s * t;
        }
    }

    template<typename T>
    inline Quaternion<T>::Quaternion(const Matrix4<T>& matrix)
    {
        *this = Quaternion(matrix.getMatrix3(3, 3));
    }

    template<typename T>
    inline Quaternion<T>::~Quaternion()
    { }


    // Public

    template<typename T>
    inline bool Quaternion<T>::isIdentity() const
    {
        return *this == identity;
    }

    template<typename T>
    inline T Quaternion<T>::dot(const Quaternion<T>& other) const
    {
        return w * other.w + vector.dot(other.vector);
    }

    template<typename T>
    inline T Quaternion<T>::dot(const Quaternion<T>& quat1, const Quaternion<T>& quat2)
    {
        return quat1.dot(quat2);
    }

    template<typename T>
    inline double Quaternion<T>::lengthSquared() const
    {
        return w*w + vector.lengthSquared();
    }

    template<typename T>
    inline double Quaternion<T>::length() const
    {
        return sqrt(lengthSquared());
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::conjugate() const
    {
        return Quaternion<T>(w, -vector);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::inverse() const
    {
        // Quaternion inverse is conjugate / |q|^2
        return conjugate() / static_cast<T>(lengthSquared());
    }

    template<typename T>
    inline Quaternion<T>& Quaternion<T>::normalize()
    {
        return *this = unitQuaternion();
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::unitQuaternion() const
    {
        return *this / static_cast<T>(length());
    }

    template<typename T>
    inline Matrix3<T> Quaternion<T>::toMatrix3() const
    {
        const double l = length();
        const T s = static_cast<T>(equals<double>(l, 0) ? 0 : 2 / l);

        const T wx = s * w * vector.x;
        const T wy = s * w * vector.y;
        const T wz = s * w * vector.z;

        const T xx = s * vector.x * vector.x;
        const T xy = s * vector.x * vector.y;
        const T xz = s * vector.x * vector.z;

        const T yy = s * vector.y * vector.y;
        const T yz = s * vector.y * vector.z;

        const T zz = s * vector.z * vector.z;

        return Matrix3<T>(1 - (yy + zz),      xy - wz,      xz + wy,
                               xy + wz,  1 - (xx + zz),     yz - wx,
                               xz - wy,       yz + wx, 1 - (xx + yy));
    }

    template<typename T>
    inline Matrix4<T> Quaternion<T>::toMatrix4() const
    {
        return Matrix4<T>(toMatrix3());
    }

    template<typename T>
    inline bool Quaternion<T>::isUnitQuaternion() const
    {
        // LengthSquared returns double.
        // Also sqrt(1) == 1 so we don't need to do that
        return equals<double>(this->lengthSquared(), 1);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::createRotation(const Vector3<T>& axis, const T& angle)
    {
        const T l = static_cast<T>(axis.length());
        return Quaternion<T>(cos<T>(angle/2), (sin<T>(angle/2) / l) * axis);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::createRotationX(const T& angle)
    {
        return createRotation(Vector3<T>(1, 0, 0), angle);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::createRotationY(const T& angle)
    {
        return createRotation(Vector3<T>(0, 1, 0), angle);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::createRotationZ(const T& angle)
    {
        return createRotation(Vector3<T>(0, 0, 1), angle);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, const T& t)
    {
        assert(q1.isUnitQuaternion() && q2.isUnitQuaternion());

        const T angle = std::acos(q1.dot(q2));

        return (std::sin((1 - t) * angle) / std::sin(angle)) * q1 + (std::sin(t*angle)/std::sin(angle)) * q2;
    }

    // Operators
    #pragma region Operators
    // Comparison
    template<typename T>
    inline bool Quaternion<T>::operator ==(const Quaternion<T>& right) const
    {
        return equals<T>(w, right.w) && vector == right.vector;
    }

    template<typename T>
    inline bool Quaternion<T>::operator !=(const Quaternion<T>& right) const
    {
        return !(*this == right);
    }

    // Arithmetic
    template<typename T>
    inline Quaternion<T> Quaternion<T>::operator +(const Quaternion<T>& right) const
    {
        return Quaternion<T>(w + right.w, vector + right.vector);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::operator -(const Quaternion<T>& right) const
    {
        return Quaternion<T>(w - right.w, vector - right.vector);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::operator -() const
    {
        return Quaternion<T>(-w , -vector);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::operator *(const Quaternion<T>& right) const
    {
        return Quaternion<T>(w * right.w - vector.dot(right.vector),
            w * right.vector + right.w*vector + vector.cross(right.vector));
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::operator *(const T& right) const
    {
        return Quaternion<T>(w * right, vector * right);
    }

    template<typename T>
    inline Quaternion<T> Quaternion<T>::operator /(const T& right) const
    {
        return Quaternion<T>(w / right, vector / right);
    }

    // Assingment
    template<typename T>
    inline Quaternion<T>& Quaternion<T>::operator =(const Quaternion<T>& right)
    {
        w = right.w;
        vector = right.vector;

        return *this;
    }

    template<typename T>
    inline Quaternion<T>& Quaternion<T>::operator +=(const Quaternion<T>& right)
    {
        *this = *this + right;

        return *this;
    }

    template<typename T>
    inline Quaternion<T>& Quaternion<T>::operator -=(const Quaternion<T>& right)
    {
        *this = *this - right;

        return *this;
    }

    template<typename T>
    inline Quaternion<T>& Quaternion<T>::operator *=(const Quaternion<T>& right)
    {
        *this = *this * right;

        return *this;
    }

    template<typename T>
    inline Quaternion<T>& Quaternion<T>::operator *=(const T& right)
    {
        *this = *this * right;

        return *this;
    }

    template<typename T>
    inline Quaternion<T>& Quaternion<T>::operator /=(const T& right)
    {
        *this = *this / right;

        return *this;
    }

    template<typename T>
    inline Quaternion<T> operator *(const T& left, const Quaternion<T>& right)
    {
        return right * left;
    }

    template<typename T>
    inline Vector3<T> operator *(const Vector3<T>& left, const Quaternion<T>& right)
    {
        const Vector3<T> rightleftCross = right.vector.cross(left);

        return left + (right.w*2)*rightleftCross + right.vector.cross(rightleftCross)*2;
    }

    template<typename T>
    inline Vector3<T> operator *(const Quaternion<T>& left, const Vector3<T>& right)
    {
        return right * left;
    }

    // Multiply a homogeneous vector e.g. (x,y,z,1)
    template<typename T>
    inline Vector4<T> operator *(const Vector4<T>& left, const Quaternion<T>& right)
    {
        // Extract x, y and z
        const Vector3<T> vec3(left.x, left.y, left.z);

        return Vector4<T>(vec3 * right, left.w);
    }

    template<typename T>
    inline Vector4<T> operator *(const Quaternion<T>& left, const Vector4<T>& right)
    {
        return right * left;
    }
    
    template<typename T>
    inline Vector3<T>& operator *=(Vector3<T>& left, const Quaternion<T>& right)
    {
        left = left * right;

        return left;
    }

    template<typename T>
    inline Vector4<T>& operator *=(Vector4<T>& left, const Quaternion<T>& right)
    {
        left = left * right;

        return left;
    }

    template<typename T>
    inline std::ostream& operator<<(std::ostream& out, const Quaternion<T>& right)
    {
        out << "Quat(" << right.w << ", " << right.vector << ")";

        return out;
    }
    #pragma endregion
}