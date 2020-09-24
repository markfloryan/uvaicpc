#include <iostream>
#include <vector>

struct Atom {
    double x,y;
    bool fixed;
    std::vector<Atom*> atoms;
    Atom(double x, double y, bool fixed){
        this->x = x;
        this->y = y;
        this->fixed = fixed;
    }
};

int main(){
    int n, m;
    std::cin >> n >> m;
    Atom** atoms = new Atom*[n];
    for(int i = 0; i < n; i++){
        int x, y;
        std::cin >> x >> y;
        atoms[i] = new Atom(x, y, x >= 0);
    }
    for(int i = 0; i < m; i++){
        int a, b;
        std::cin >> a >> b;
        a -= 1;
        b -= 1;
        atoms[a]->atoms.emplace_back(atoms[b]);
        atoms[b]->atoms.emplace_back(atoms[a]);
    }
    for(int i = 0; i < 20000; i++){
        for(int idx = 0; idx < n; idx++){
            auto atom = atoms[idx];
            if(!atom->fixed){
                double x = 0;
                double y = 0;
                for(auto atom2 : atom->atoms){
                    x += atom2->x;
                    y += atom2->y;
                }
                x /= atom->atoms.size();
                y /= atom->atoms.size();
                atom->x = x;
                atom->y = y;
            }
        }
    }
    for(int idx = 0; idx < n; idx++){
        auto atom = atoms[idx];
        std::cout << atom->x << " " << atom->y << std::endl;
    }
}

