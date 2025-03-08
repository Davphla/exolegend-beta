#include "Gladiator.hpp"
#include <algorithm>

double kw = 1.2;
double kv = 1.f;
double wlimit = 3.f;
double vlimit = 0.6;
double erreurPos = 0.07;

double reductionAngle(double x)
{
    x = fmod(x + PI, 2 * PI);
    if (x < 0)
        x += 2 * PI;
    return x - PI;
}
void go_to(Position cons, Position pos)
{
    double consvl, consvr;
    double dx = cons.x - pos.x;
    double dy = cons.y - pos.y;
    double d = sqrt(dx * dx + dy * dy);

    if (d > erreurPos)
    {
        double rho = atan2(dy, dx);
        double alpha = reductionAngle(rho - pos.a);

        bool reverse = (abs(alpha) > PI / 2);
        if (reverse) {
            alpha = reductionAngle(alpha + PI);
            d = -d;
        }

        double consw = kw * alpha;
        double consv = kv * d * cos(alpha);

        consw = std::clamp(consw, -wlimit, wlimit);
        consv = std::clamp(consv, -vlimit, vlimit);

        double robotRadius = gladiator->robot->getRobotRadius();
        consvl = consv - robotRadius * consw; // GFA 3.6.2
        consvr = consv + robotRadius * consw; // GFA 3.6.2
    }
    else
    {
        consvr = 0;
        consvl = 0;
    }

    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, consvr, false); // GFA 3.2.1
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, consvl, false);  // GFA 3.2.1
}
