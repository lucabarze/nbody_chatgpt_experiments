/* The Computer Language Benchmarks Game
https://salsa.debian.org/benchmarksgame-team/benchmarksgame/

contributed by Mark C. Lewis
translated to C by [Your Name]
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5
#define PI 3.141592653589793
#define SOLAR_MASS (4 * PI * PI)
#define DAYS_PER_YEAR 365.24

typedef struct {
    double x, y, z, vx, vy, vz, mass;
} Body;

void offset_momentum(Body *p, double px, double py, double pz) {
    p->vx = -px / SOLAR_MASS;
    p->vy = -py / SOLAR_MASS;
    p->vz = -pz / SOLAR_MASS;
}

Body jupiter() {
    Body p;
    p.x = 4.84143144246472090e+00;
    p.y = -1.16032004402742839e+00;
    p.z = -1.03622044471123109e-01;
    p.vx = 1.66007664274403694e-03 * DAYS_PER_YEAR;
    p.vy = 7.69901118419740425e-03 * DAYS_PER_YEAR;
    p.vz = -6.90460016972063023e-05 * DAYS_PER_YEAR;
    p.mass = 9.54791938424326609e-04 * SOLAR_MASS;
    return p;
}

Body saturn() {
    Body p;
    p.x = 8.34336671824457987e+00;
    p.y = 4.12479856412430479e+00;
    p.z = -4.03523417114321381e-01;
    p.vx = -2.76742510726862411e-03 * DAYS_PER_YEAR;
    p.vy = 4.99852801234917238e-03 * DAYS_PER_YEAR;
    p.vz = 2.30417297573763929e-05 * DAYS_PER_YEAR;
    p.mass = 2.85885980666130812e-04 * SOLAR_MASS;
    return p;
}

Body uranus() {
    Body p;
    p.x = 1.28943695621391310e+01;
    p.y = -1.51111514016986312e+01;
    p.z = -2.23307578892655734e-01;
    p.vx = 2.96460137564761618e-03 * DAYS_PER_YEAR;
    p.vy = 2.37847173959480950e-03 * DAYS_PER_YEAR;
    p.vz = -2.96589568540237556e-05 * DAYS_PER_YEAR;
    p.mass = 4.36624404335156298e-05 * SOLAR_MASS;
    return p;
}

Body neptune() {
    Body p;
    p.x = 1.53796971148509165e+01;
    p.y = -2.59193146099879641e+01;
    p.z = 1.79258772950371181e-01;
    p.vx = 2.68067772490389322e-03 * DAYS_PER_YEAR;
    p.vy = 1.62824170038242295e-03 * DAYS_PER_YEAR;
    p.vz = -9.51592254519715870e-05 * DAYS_PER_YEAR;
    p.mass = 5.15138902046611451e-05 * SOLAR_MASS;
    return p;
}

Body sun() {
    Body p;
    p.mass = SOLAR_MASS;
    return p;
}

void advance(Body bodies[], double dt) {
    for (int i = 0; i < N; ++i) {
        Body *bi = &bodies[i];
        double vx = bi->vx;
        double vy = bi->vy;
        double vz = bi->vz;
        for (int j = i + 1; j < N; ++j) {
            Body *bj = &bodies[j];
            double dx = bi->x - bj->x;
            double dy = bi->y - bj->y;
            double dz = bi->z - bj->z;

            double distance2 = dx * dx + dy * dy + dz * dz;
            double mag = dt / (distance2 * sqrt(distance2));

            double mj_mag = bj->mass * mag;
            vx -= dx * mj_mag;
            vy -= dy * mj_mag;
            vz -= dz * mj_mag;

            double mi_mag = bi->mass * mag;
            bj->vx += dx * mi_mag;
            bj->vy += dy * mi_mag;
            bj->vz += dz * mi_mag;
        }

        bi->vx = vx;
        bi->vy = vy;
        bi->vz = vz;
        bi->x += dt * vx;
        bi->y += dt * vy;
        bi->z += dt * vz;
    }
}

double energy(Body bodies[]) {
    double dx, dy, dz, distance;
    double e = 0.0;
    for (int i = 0; i < N; ++i) {
        Body *bi = &bodies[i];
        e += 0.5 * bi->mass * (bi->vx * bi->vx + bi->vy * bi->vy + bi->vz * bi->vz);

        for (int j = i + 1; j < N; ++j) {
            Body *bj = &bodies[j];
            dx = bi->x - bj->x;
            dy = bi->y - bj->y;
            dz = bi->z - bj->z;

            distance = sqrt(dx * dx + dy * dy + dz * dz);
            e -= (bi->mass * bj->mass) / distance;
        }
    }
    return e;
}

int main(int argc, char *argv[]) {
    int n = argc > 1 ? atoi(argv[1]) : 1000;
    Body bodies[] = {sun(), jupiter(), saturn(), uranus(), neptune()};
    double px = 0.0, py = 0.0, pz = 0.0;

    for (int i = 0; i < N; ++i) {
        px += bodies[i].vx * bodies[i].mass;
        py += bodies[i].vy * bodies[i].mass;
        pz += bodies[i].vz * bodies[i].mass;
    }
    offset_momentum(&bodies[0], px, py, pz);

    printf("%.9f\n", energy(bodies));

    for (int i = 0; i < n; ++i) {
        advance(bodies, 0.01);
    }

    printf("%.9f\n", energy(bodies));

    return 0;
}

