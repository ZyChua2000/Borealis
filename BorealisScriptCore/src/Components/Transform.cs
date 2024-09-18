

namespace Borealis
{
    public class Transform : Component
    {
        //public int childCount;
        public Vector3 eulerAngles
        {
            get
            {
                InternalCalls.TransformComponent_GetRotation(gameObject.GetInstanceID(), out Vector3 rotation);
                return rotation;
            }
            set
            {
                InternalCalls.TransformComponent_SetRotation(gameObject.GetInstanceID(), ref value);
            }
        }
        public Vector3 localScale
        {
            get
            {
                InternalCalls.TransformComponent_GetScale(gameObject.GetInstanceID(), out Vector3 scale);
                return scale;
            }
            set
            {
                InternalCalls.TransformComponent_SetScale(gameObject.GetInstanceID(), ref value);
            }
        }
        public Vector3 position
        {
            get
            {
                InternalCalls.TransformComponent_GetTranslation(gameObject.GetInstanceID(), out Vector3 translation);
                return translation;
            }
            set
            {
                InternalCalls.TransformComponent_SetTranslation(gameObject.GetInstanceID(), ref value);
            }

        }
    }
}
