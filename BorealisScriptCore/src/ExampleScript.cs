
using System;


namespace Borealis
{
    public class ExampleScript : MonoBehaviour
    {
        bool speed;

        public ExampleScript()
        {
            speed = true;
        }
        
        public override void Start()
        {
            Console.WriteLine("Hello World!");
        }

        public override void Update()
        {
            if (speed)
            {
                Console.WriteLine("Speed is true");
            }
            else
            {
                Console.WriteLine("Speed is false");
            }
        }
       
    }
}
