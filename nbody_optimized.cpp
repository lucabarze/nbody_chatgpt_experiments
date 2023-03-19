#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>

struct Body {
    double x, y, z;
    double vx, vy, vz;
    double mass;
};

const double pi = 3.141592653589793;
const double solar_mass = 4 * pi * pi;
const double days_per_year = 365.24;
const double dt = 0.01;

const Body sun = {0, 0, 0, 0, 0, 0, solar_mass};

const Body jupiter = {4.84143144246472090e+00,
    -1.16032004402742839e+00,
    -1.03622044471123109e-01,
    1.66007664274403694e-03 * days_per_year,
    7.69901118419740425e-03 * days_per_year,
    -6.90460016972063023e-05 * days_per_year,
    9.54791938424326609e-04 * solar_mass};

const Body saturn = {8.34336671824457987e+00,
    4.12479856412430479e+00,
    -4.03523417114321381e-01,
    -2.76742510726862411e-03 * days_per_year,
    4.99852801234917238e-03 * days_per_year,
    2.30417297573763929e-05 * days_per_year,
    2.85885980666130812e-04 * solar_mass};

const Body uranus = {1.28943695621391310e+01,
    -1.51111514016986312e+01,
    -2.23307578892655734e-01,
    2.96460137564761618e-03 * days_per_year,
    2.37847173959480950e-03 * days_per_year,
    -2.96589568540237556e-05 * days_per_year,
    4.36624404335156298e-05 * solar_mass};

const Body neptune = {1.53796971148509165e+01,
    -2.59193146099879641e+01,
    1.79258772950371181e-01,
    2.68067772490389322e-03 * days_per_year,
    1.62824170038242295e-03 * days_per_year,
    -9.51592254519715870e-05 * days_per_year,
    5.15138902046611451e-05 * solar_mass};

std::vector<Body> solar_system = {sun, jupiter, saturn, uranus, neptune};

void advance() {
    for (size_t i = 0; i < solar_system.size(); ++i) {
        for (size_t j = i + 1; j < solar_system.size(); ++j) {
            double dx = solar_system[i].x - solar_system[j].x;
            double dy = solar_system[i].y - solar_system[j].y;
            double dz = solar_system[i].z - solar_system[j].z;
            double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
            double mag = dt / (distance * distance * distance);
            solar_system[i].vx -= dx * solar_system[j].mass * mag;
            solar_system[i].vy -= dy * solar_system[j].mass * mag;
            solar_system[i].vz -= dz * solar_system[j].mass * mag;
            solar_system[j].vx += dx * solar_system[i].mass * mag;
            solar_system[j].vy += dy * solar_system[i].mass * mag;
            solar_system[j].vz += dz * solar_system[i].mass * mag;
        }
    }
    for (Body &body : solar_system) {
        body.x += dt * body.vx;
        body.y += dt * body.vy;
        body.z += dt * body.vz;
    }

}

double energy() {
    double e = 0.0;
    for (size_t i = 0; i < solar_system.size(); ++i) {
        e += 0.5 * solar_system[i].mass * (solar_system[i].vx * solar_system[i].vx + solar_system[i].vy * solar_system[i].vy + solar_system[i].vz * solar_system[i].vz);
        for (size_t j = i + 1; j < solar_system.size(); ++j) {
            double dx = solar_system[i].x - solar_system[j].x;
            double dy = solar_system[i].y - solar_system[j].y;
            double dz = solar_system[i].z - solar_system[j].z;
            double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
            e -= (solar_system[i].mass * solar_system[j].mass) / distance;
        }
    }
    return e;
}

void offset_momentum() {
    double px = 0.0, py = 0.0, pz = 0.0;
    for (const Body &body : solar_system) {
        px += body.vx * body.mass;
        py += body.vy * body.mass;
        pz += body.vz * body.mass;
    }

    solar_system[0].vx = -px / solar_mass;
    solar_system[0].vy = -py / solar_mass;
    solar_system[0].vz = -pz / solar_mass;

}

int main(int argc, char **argv) {
    offset_momentum();

    printf("%.9f\n", energy());

    int n = std::atoi(argv[1]);

    for (int i = 1; i <= n; ++i) {
        advance();
    }

    printf("%.9f\n", energy());

    return 0;

}

