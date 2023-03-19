#include <stdio.h>
#include <math.h>

#define PI            3.141592653589793
#define SOLAR_MASS    (4 * PI * PI)
#define DAYS_PER_YEAR 365.24

double energy();
void advance(double);
void offset_momentum();

double xs[5] = {0, 4.84143144246472090e+00, 8.34336671824457987e+00,
    1.28943695621391310e+01, 1.53796971148509165e+01};
double ys[5] = {0, -1.16032004402742839e+00, 4.12479856412430479e+00,
    -1.51111514016986312e+01, -2.59193146099879641e+01};
double zs[5] = {0, -1.03622044471123109e-01, -4.03523417114321381e-01,
    -2.23307578892655734e-01, 1.79258772950371181e-01};
double vxs[5] = {0, 1.66007664274403694e-03 * DAYS_PER_YEAR,
    -2.76742510726862411e-03 * DAYS_PER_YEAR,
    2.96460137564761618e-03 * DAYS_PER_YEAR,
    2.68067772490389322e-03 * DAYS_PER_YEAR};
double vys[5] = {0, 7.69901118419740425e-03 * DAYS_PER_YEAR,
    4.99852801234917238e-03 * DAYS_PER_YEAR,
    2.37847173959480950e-03 * DAYS_PER_YEAR,
    1.62824170038242295e-03 * DAYS_PER_YEAR};
double vzs[5] = {0, -6.90460016972063023e-05 * DAYS_PER_YEAR,
    2.30417297573763929e-05 * DAYS_PER_YEAR,
    -2.96589568540237556e-05 * DAYS_PER_YEAR,
    -9.51592254519715870e-05 * DAYS_PER_YEAR};
double mass[5] = {1 * SOLAR_MASS, 9.54791938424326609e-04 * SOLAR_MASS,
    2.85885980666130812e-04 * SOLAR_MASS,
    4.36624404335156298e-05 * SOLAR_MASS,
    5.15138902046611451e-05 * SOLAR_MASS};

const int last = 4;

double energy()
{
    double e = 0.0;
    double dx, dy, dz, distance;
    for (int i = 0; i < last + 1; i++)
    {
        e += 0.5 * mass[i] *
            (vxs[i] * vxs[i] + vys[i] * vys[i] + vzs[i] * vzs[i]);
        for (int j = i + 1; j < last + 1; j++)
        {
            dx = xs[i] - xs[j];
            dy = ys[i] - ys[j];
            dz = zs[i] - zs[j];
            distance = sqrt(dx * dx + dy * dy + dz * dz);
            e -= (mass[i] * mass[j]) / distance;
        }
    }
    return e;
}

void advance(double dt)
{
    double mm, mm2, dx, dy, dz, distance, mag;
    for (int i = 0; i < last + 1; i++)
    {
        for (int j = i + 1; j < last + 1; j++)
        {
            dx = xs[i] - xs[j];
            dy = ys[i] - ys[j];
            dz = zs[i] - zs[j];
            distance = sqrt(dx * dx + dy * dy + dz * dz);
            mag = dt / (distance * distance * distance);
            mm = mass[i] * mag;
            mm2 = mass[j] * mag;
            vxs[i] -= dx * mm2;
            vxs[j] += dx * mm;
            vys[i] -= dy * mm2;
            vys[j] += dy * mm;
            vzs[i] -= dz * mm2;
            vzs[j] += dz * mm;
        }
    }
    for (int i = 0; i < last + 1; i++)
    {
        xs[i] += dt * vxs[i];
        ys[i] += dt * vys[i];
        zs[i] += dt * vzs[i];
    }
}

void offset_momentum()
{
    double px = 0.0, py = 0.0, pz = 0.0, mass_i;
    for (int i = 0; i < last + 1; i++)
    {
        mass_i = mass[i];
        px += vxs[i] * mass_i;
        py += vys[i] * mass_i;
        pz += vzs[i] * mass_i;
    }
    vxs[0] = -px / SOLAR_MASS;
    vys[0] = -py / SOLAR_MASS;
    vzs[0] = -pz / SOLAR_MASS;
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    n = sscanf(argv[1], "%d", &n) ? n : 1000;

    offset_momentum();
    printf("%.9f\n", energy());

    for (int i = 0; i < n; i++)
    {
        advance(0.01);
    }

    printf("%.9f\n", energy());
    return 0;
}
