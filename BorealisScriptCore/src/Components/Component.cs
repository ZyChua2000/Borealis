namespace Borealis
{
    public class Component : Object
    {
        public GameObject gameObject { get; internal set; }
        public Transform transform
        {
            get
            {
                return gameObject.transform;
            }
            set
            {
                gameObject.transform = value;
            }
        }
    }
}
