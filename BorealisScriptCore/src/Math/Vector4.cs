using System;
namespace Borealis
{
    public struct Vector4
    {

        public static Vector4 negativeInfinity => new Vector4(float.NegativeInfinity, float.NegativeInfinity, float.NegativeInfinity, float.NegativeInfinity);
        public static Vector4 one => new Vector4(1, 1, 1, 1);
        public static Vector4 positiveInfinity => new Vector4(float.PositiveInfinity, float.PositiveInfinity, float.PositiveInfinity, float.PositiveInfinity);
        public static Vector4 zero => new Vector4(0, 0, 0, 0);

        public float magnitude
        {
            get
            {
                return Mathf.Sqrt(w * w + x * x + y * y + z * z);
            }
        }

        public Vector4 normalized
        {
            get
            {
                return Normalized(this);
            }
        }
        public float sqrMagnitude
        {
            get
            {
                return w * w + x * x + y * y + z * z;
            }
        }

        public float this[int index]
        {
            get
            {
                if (index == 0) return x;
                if (index == 1) return y;
                if (index == 2) return z;
                if (index == 3) return w;
                throw new IndexOutOfRangeException("Invalid index for Vector4");
            }
            set
            {
                if (index == 0) x = value;
                else if (index == 1) y = value;
                else if (index == 2) z = value;
                else if (index == 3) w = value;
                else throw new IndexOutOfRangeException("Invalid index for Vector4");
            }
        }

        public float w;
        public float x;
        public float y;
        public float z;

        public Vector4(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        // Public Methods
        public override bool Equals(object obj)
        {
            return obj is Vector4 other && x == other.x && y == other.y && z == other.z && w == other.w;
        }

        public override int GetHashCode()
        {
            return (x, y, z, w).GetHashCode();
        }

        public void Set(float newX, float newY, float newZ, float newW)
        {
            x = newX;
            y = newY;
            z = newZ;
            w = newW;
        }

        public override string ToString()
        {
            return $"({x}, {y}, {z}, {w})";
        }

        // Static Methods
        public static float Distance(Vector4 a, Vector4 b)
        {
            return (a - b).magnitude;
        }

        public static float Dot(Vector4 a, Vector4 b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }

        public static Vector4 Lerp(Vector4 a, Vector4 b, float t)
        {
            t = Mathf.Clamp01(t);
            return new Vector4(Mathf.Lerp(a.x, b.x, t), Mathf.Lerp(a.y, b.y, t), Mathf.Lerp(a.z, b.z, t), Mathf.Lerp(a.w, b.w, t));
        }

        public static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t)
        {
            return new Vector4(Mathf.LerpUnclamped(a.x, b.x, t), Mathf.LerpUnclamped(a.y, b.y, t), Mathf.LerpUnclamped(a.z, b.z, t), Mathf.LerpUnclamped(a.w, b.w, t));
        }

        public static Vector4 Max(Vector4 a, Vector4 b)
        {
            return new Vector4(Mathf.Max(a.x, b.x), Mathf.Max(a.y, b.y), Mathf.Max(a.z, b.z), Mathf.Max(a.w, b.w));
        }

        public static Vector4 Min(Vector4 a, Vector4 b)
        {
            return new Vector4(Mathf.Min(a.x, b.x), Mathf.Min(a.y, b.y), Mathf.Min(a.z, b.z), Mathf.Min(a.w, b.w));
        }

        public static Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta)
        {
            Vector4 a = target - current;
            float magnitude = a.magnitude;
            if (magnitude <= maxDistanceDelta || magnitude == 0)
            {
                return target;
            }
            return current + a / magnitude * maxDistanceDelta;
        }

        public static Vector4 Normalize(Vector4 a)
        {
            return a.normalized;
        }

        public static Vector4 Project(Vector4 a, Vector4 b)
        {
            return b * Dot(a, b) / Dot(b, b);
        }

        public static Vector4 Scale(Vector4 a, Vector4 b)
        {
            return new Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
        }

        // Operators
        public static Vector4 operator +(Vector4 a, Vector4 b)
        {
            return new Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
        }

        public static Vector4 operator /(Vector4 a, float d)
        {
            return new Vector4(a.x / d, a.y / d, a.z / d, a.w / d);
        }

        public static bool operator ==(Vector4 a, Vector4 b)
        {
            return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
        }

        public static bool operator !=(Vector4 a, Vector4 b)
        {
            return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
        }

        public static Vector4 operator *(Vector4 a, float d)
        {
            return new Vector4(a.x * d, a.y * d, a.z * d, a.w * d);
        }

        public static Vector4 operator *(float d, Vector4 a)
        {
            return new Vector4(a.x * d, a.y * d, a.z * d, a.w * d);
        }

        public static Vector4 operator -(Vector4 a, Vector4 b)
        {
            return new Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
        }

        public static implicit operator Vector4(Vector3 v)
        {
            return new Vector4(v.x, v.y, v.z, 0);
        }

        public static implicit operator Vector3(Vector4 v)
        {
            return new Vector3(v.x, v.y, v.z);
        }

        public static implicit operator Vector4(Vector2 v)
        {
            return new Vector4(v.x, v.y, 0, 0);
        }

        public static implicit operator Vector2(Vector4 v)
        {
            return new Vector2(v.x, v.y);
        }


        private static Vector4 Normalized(Vector4 a)
        {
            float magnitude = a.magnitude;
            if (magnitude > 9.99999974737875E-06)
            {
                return a / magnitude;
            }
            return zero;
        }
    }
}
