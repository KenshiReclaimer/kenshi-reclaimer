using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Reclaimer.Shinobi
{
    [AttributeUsage(AttributeTargets.Delegate)]
    public class NativeHookAttribute : NativeAddressAttribute
    {

        CallingConvention callingConvention;
    }
}
