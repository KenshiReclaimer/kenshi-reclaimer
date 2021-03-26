using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Reclaimer.Shinobi
{
    public class ByteSignatureAttribute : Attribute
    {
        public ByteSignatureAttribute(string signature)
        {
            this.signature = signature;
        }

        public string signature;
    }
}
