#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SOLAR_MASS (4 * M_PI * M_PI)
#define DAYS_PER_YEAR 365.24

typedef struct {
    double x, y, z, vx, vy, vz, mass;
} Planet;

void initialize_planet(Planet *planet, double x, double y, double z, double vx, double vy, double vz, double mass) {
    planet->x = x;
    planet->y = y;
    planet->z = z;
    planet->vx = vx * DAYS_PER_YEAR;
    planet->vy = vy * DAYS_PER_YEAR;
    planet->vz = vz * DAYS_PER_YEAR;
    planet->mass = mass * SOLAR_MASS;
}

void move_from_i(Planet *planet, Planet bodies[], int nbodies, double dt, int i) {
    while (i < nbodies) {
        Planet *b2 = &bodies[i];
        double dx = planet->x - b2->x;
        double dy = planet->y - b2->y;
        double dz = planet->z - b2->z;

        double distance = sqrt(dx * dx + dy * dy + dz * dz);
        double mag = dt / (distance * distance * distance);
        double b_mass_mag = planet->mass * mag;
        double b2_mass_mag = b2->mass * mag;

        planet->vx -= dx * b2_mass_mag;
        planet->vy -= dy * b2_mass_mag;
        planet->vz -= dz * b2_mass_mag;
        b2->vx += dx * b_mass_mag;
        b2->vy += dy * b_mass_mag;
        b2->vz += dz * b_mass_mag;
        i += 1;
    }

    planet->x += dt * planet->vx;
    planet->y += dt * planet->vy;
    planet->z += dt * planet->vz;
}

double energy(Planet bodies[], int nbodies) {
    double e = 0.0;

    for (int i = 0; i < nbodies; i++) {
        Planet *b = &bodies[i];
        e += 0.5 * b->mass * (b->vx * b->vx + b->vy * b->vy + b->vz * b->vz);
        for (int j = i + 1; j < nbodies; j++) {
            Planet *b2 = &bodies[j];
            double dx = b->x - b2->x;
            double dy = b->y - b2->y;
            double dz = b->z - b2->z;
            double distance = sqrt(dx * dx + dy * dy + dz * dz);
            e -= (b->mass * b2->mass) / distance;
        }
    }
    return e;
}

void offset_momentum(Planet bodies[], int nbodies) {
    double px = 0.0, py = 0.0, pz = 0.0;

    for (int i = 0; i < nbodies; i++) {
        Planet *b = &bodies[i];
        double m = b->mass;
        px += b->vx * m;
        py += b->vy * m;
        pz += b->vz * m;
    }

    Planet *b = &bodies[0];
    b->vx = - px / SOLAR_MASS;
    b->vy = - py / SOLAR_MASS;
    b->vz = - pz / SOLAR_MASS;

}

int main(int argc, char *argv[]) {
    Planet BODIES[] = {
        // sun
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 * SOLAR_MASS},
        // jupiter
        {4.84143144246472090e+00, -1.16032004402742839e+00, -1.03622044471123109e-01, 1.66007664274403694e-03, 7.69901118419740425e-03, -6.90460016972063023e-05, 9.54791938424326609e-04 * SOLAR_MASS},

        // saturn
        {8.34336671824457987e+00, 4.12479856412430479e+00, -4.03523417114321381e-01, -2.76742510726862411e-03, 4.99852801234917238e-03, 2.30417297573763929e-05, 2.85885980666130812e-04 * SOLAR_MASS},

        // uranus
        {1.28943695621391310e+01, -1.51111514016986312e+01, -2.23307578892655734e-01, 2.96460137564761618e-03, 2.37847173959480950e-03, -2.96589568540237556e-05, 4.36624404335156298e-05 * SOLAR_MASS},

        // neptune
        {1.53796971148509165e+01, -2.59193146099879641e+01, 1.79258772950371181e-01, 2.68067772490389322e-03, 1.62824170038242295e-03, -9.51592254519715870e-05, 5.15138902046611451e-05 * SOLAR_MASS}
    };

    int n = atoi(argv[1]);

    offset_momentum(BODIES, sizeof(BODIES) / sizeof(BODIES[0]));

    printf("%.9f\n", energy(BODIES, sizeof(BODIES) / sizeof(BODIES[0])));

    int nbodies = sizeof(BODIES) / sizeof(BODIES[0]);
    double dt = 0.01;

    for (int t = 0; t < n; t++) {
        for (int i = 0; i < nbodies; i++) {
            Planet *b = &BODIES[i];
            move_from_i(b, BODIES, nbodies, dt, i + 1);
        }
    }

    printf("%.9f\n", energy(BODIES, sizeof(BODIES) / sizeof(BODIES[0])));

    return 0;
}
