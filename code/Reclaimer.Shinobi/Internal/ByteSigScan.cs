using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Reclaimer.Shinobi.Internal
{
    public class ByteSigScan : IScan
    {
        public ByteSigScan(string signature)
        {
            string[] bytes = signature.Split(' ');
            signatureBytes = new byte[bytes.Length];
            mask = "";

            for (var i = 0; i < bytes.Length; i++)
            {
                if (bytes[i] == "?" || bytes[i] == "??")
                {
                    mask += "?";
                    signatureBytes[i] = 0x00;
                }
                else
                {
                    signatureBytes[i] = Convert.ToByte(bytes[i]);
                    mask += "x";
                }
            }
        }

        public IntPtr Resolve(ReadOnlySpan<byte> memory)
        {
            byte first = signatureBytes[0];
            for(var i = 0; i < (memory.Length - signatureBytes.Length); i++)
            {
                bool found = true;
                if (memory[i] != first)
                {
                    continue;
                }
                for(int j = 0; j < signatureBytes.Length; j++)
                {
                    if (mask[j] == 'x' && memory[i+j] == signatureBytes[j])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    return new IntPtr(i);
                }
            }
            return IntPtr.Zero;
        }

        byte[] signatureBytes;
        string mask;
    }
}
