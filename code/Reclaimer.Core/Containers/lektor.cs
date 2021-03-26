using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Reclaimer.Core.Containers
{
    [StructLayout(LayoutKind.Explicit)]
    public class lektor<T>
    {
        [FieldOffset(0)] 
        IntPtr vtbl;

        [FieldOffset(0x8)] 
        uint cap;

        [FieldOffset(0xC)] 
        uint len;

        [FieldOffset(0x10)] 
        IntPtr data;
    }
}
