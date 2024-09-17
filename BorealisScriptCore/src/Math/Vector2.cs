
using System;
using System.Threading;


namespace Borealis
{
    public struct Vector2
    {
        // Constructor
       public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        // Static Properties
        public static Vector2 zero => new Vector2(0, 0);
        public static Vector2 one => new Vector2(1, 1);
        public static Vector2 up => new Vector2(0, 1);
        public static Vector2 down => new Vector2(0, -1);
        public static Vector2 left => new Vector2(-1, 0);
        public static Vector2 right => new Vector2(1, 0);
        public static Vector2 negativeInfinity => new Vector2(float.NegativeInfinity, float.NegativeInfinity);
        public static Vector2 positiveInfinity => new Vector2(float.PositiveInfinity, float.PositiveInfinity);

        // Properties
        public float x;
        public float y;
        
        public float magnitude 
        { 
            get
            {
                return Mathf.Sqrt(y * y + x * x);
            }
        }
        public Vector2 normalized
        {
            get
            {
                return Normalize(this);
            }
        }
        public float sqrMagnitude 
        { 
            get
            {
                return x * x + y * y;
            }
                
         }
        public float this[int index]
        {
            get
            {
                if (index == 0) return x;
                if (index == 1) return y;
                throw new IndexOutOfRangeException("Invalid index for Vector2");
            }
            set
            {
                if (index == 0) x = value;
                else if (index == 1) y = value;
                else throw new IndexOutOfRangeException("Invalid index for Vector2");
            }
        }

       
        // Public methods
        public override bool Equals(object obj)
        {
            if (obj is Vector2)
            {
                Vector2 other = (Vector2)obj;
                return x == other.x && y == other.y;
            }
            return false;
        }
        public override int GetHashCode()
        {
            return (x, y).GetHashCode();
        }

        public void Normalize()
        {
            float mag = magnitude;
            if (mag > 0)
            {
                x /= mag;
                y /= mag;
            }
        }

        public void Set(float newX, float newY)
        {
            this.x = newX;
            this.y = newY;
        }

        public override string ToString()
        {
            return $"({x}, {y})";
        }

        // Static Methods
        public static float Angle(Vector2 from, Vector2 to)
        {
            return Mathf.Acos(Dot(from.normalized, to.normalized)) * Mathf.Rad2Deg;
        }

        public static Vector2 ClampMagnitude(Vector2 vector, float maxLength)
        {
            if (vector.sqrMagnitude > maxLength * maxLength)
            {
                return vector.normalized * maxLength;
            }
            return vector;
        }

        public static float Distance(Vector2 a, Vector2 b)
        {
            return (a - b).magnitude;
        }

        public static float Dot(Vector2 lhs, Vector2 rhs)
        {
            return lhs.x * rhs.x + lhs.y * rhs.y;
        }

        public static Vector2 Lerp(Vector2 a, Vector2 b, float t)
        {
            t = Mathf.Clamp01(t);
            return new Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
        }

        public static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t)
        {
            return new Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
        }
        public static Vector2 Max(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(Mathf.Max(lhs.x, rhs.x), Mathf.Max(lhs.y, rhs.y));
        }

        public static Vector2 Min(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(Mathf.Min(lhs.x, rhs.x), Mathf.Min(lhs.y, rhs.y));
        }

        public static Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta)
        {
            Vector2 a = target - current;
            float magnitude = a.magnitude;
            if (magnitude <= maxDistanceDelta || magnitude == 0f)
            {
                return target;
            }
            return current + a / magnitude * maxDistanceDelta;
        }

        public static Vector2 Perpendicular(Vector2 inDirection)
        {
            return new Vector2(-inDirection.y, inDirection.x);
        }

        public static Vector2 Reflect(Vector2 inDirection, Vector2 inNormal)
        {
            return inDirection - 2 * Dot(inDirection, inNormal) * inNormal;
        }

        public static Vector2 Scale(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x * b.x, a.y * b.y);
        }

        public static float SignedAngle(Vector2 from, Vector2 to)
        {
            float angle = Angle(from, to);
            float sign = (from.x * to.y - from.y * to.x) < 0 ? -1f : 1f;
            return angle * sign;
        }
        public static Vector2 SmoothDamp(Vector2 current, Vector2 target, ref Vector2 velocity, float smoothTime, float maxSpeed = float.PositiveInfinity, float deltaTime = 0.02f)
        {
            smoothTime = Math.Max(0.0001f, smoothTime);
            float omega = 2f / smoothTime;
            float x = omega * deltaTime;
            float exp = 1f / (1f + x + 0.48f * x * x + 0.235f * x * x * x);
            Vector2 change = current - target;
            Vector2 originalTo = target;
            float maxChange = maxSpeed * smoothTime;
            change = ClampMagnitude(change, maxChange);
            target = current - change;
            Vector2 temp = (velocity + omega * change) * deltaTime;
            velocity = (velocity - omega * temp) * exp;
            Vector2 output = target + (change + temp) * exp;
            if (Dot(originalTo - current, output - originalTo) > 0f)
            {
                output = originalTo;
                velocity = (output - originalTo) / deltaTime;
            }
            return output;
        }


        // Operators
        public static Vector2 operator +(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x + b.x, a.y + b.y);
        }

        public static Vector2 operator -(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x - b.x, a.y - b.y);
        }

        public static Vector2 operator *(Vector2 a, float d)
        {
            return new Vector2(a.x * d, a.y * d);
        }

        public static Vector2 operator *(float d, Vector2 a)
        {
            return new Vector2(a.x * d, a.y * d);
        }

        public static Vector2 operator /(Vector2 a, float d)
        {
            return new Vector2(a.x / d, a.y / d);
        }

        public static bool operator ==(Vector2 lhs, Vector2 rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        public static bool operator !=(Vector2 lhs, Vector2 rhs)
        {
            return !(lhs == rhs);
        }

        public static implicit operator Vector2(Vector3 v)
        {
            return new Vector2(v.x, v.y);
        }

        public static implicit operator Vector3(Vector2 v)
        {
            return new Vector3(v.x, v.y, 0);
        }

        private static Vector2 Normalize(Vector2 vector)
        {
            float magnitude = vector.magnitude;
            if (magnitude > 1e-5)
            {
                return vector / magnitude;
            }
            return zero;
        }

    }
}
