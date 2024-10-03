
using System;


namespace Borealis
{
    public class CameraController : MonoBehaviour
    {
        public override void Start()
        {
        }

        public override void Update()
        {
            if (Input.GetKey(KeyCode.W))
            {
                transform.position += new Vector3(0, 0, 1);
            }
            if (Input.GetKey(KeyCode.S))
            {
                transform.position += new Vector3(0, 0, -1);
            }
            if (Input.GetKey(KeyCode.A))
            {
                transform.position += new Vector3(-1, 0, 0);
            }
            if (Input.GetKey(KeyCode.D))
            {
                transform.position += new Vector3(1, 0, 0);
            }

            if (Input.GetKey(KeyCode.Space))
            {
                transform.position += new Vector3(0, 1, 0);
            }
            if (Input.GetKey(KeyCode.LeftShift))
            {
                transform.position += new Vector3(0, -1, 0);
            }
        }

    }
}
