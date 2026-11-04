#include <circle/startup.h>     // for EXIT_HALT
#include <circle/actled.h>
#include <circle/timer.h>

int main (void)
{
        CActLED ActLED;

        for (unsigned i = 1; i <= 10; i++)
        {
                ActLED.On ();
                CTimer::SimpleMsDelay (200);

                ActLED.Off ();
                CTimer::SimpleMsDelay (500);
        }

        return EXIT_HALT;
}