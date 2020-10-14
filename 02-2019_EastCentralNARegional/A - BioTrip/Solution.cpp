#include <vector>
#include <iostream>
#include <queue>

struct junction;

struct connection {
	junction* start;
	junction* dst;
	int cost;

	int exitAngle;
	int entryAngle;

	int best{ -1 };

	connection(junction* start, junction* dst, int cost, int entry) : start{ start }, dst{ dst }, entryAngle{ entry }, 
		cost{ cost }{}
	void calcExit();
};
struct junction {
	int number;
	std::vector<connection*> connections;
	junction(int number) : number{ number }{}
	std::vector<connection*> calcValids(connection* in, int angle1, int angle2){
		std::vector<connection*> valids{};

		for(auto connection : connections){
			int diff = (connection->entryAngle - in->exitAngle + 360) % 360;
			diff = diff > 180 ? diff - 360 : diff;
			if(diff == 180){
				if(angle1 == 180 || angle2 == 180){
					valids.emplace_back(connection);
				}
			} else if(diff >= 0 && diff <= angle1 || diff < 0 && -diff <= angle2){
				valids.emplace_back(connection);
			}
		}
		return valids;
	}
};
void connection::calcExit(){
	for(auto con : dst->connections){
		if(con->dst == start){
			exitAngle = (con->entryAngle + 180) % 360;
			exitAngle = exitAngle > 180 ? exitAngle - 360 : exitAngle;
		}
	}
}
void recurse(connection* at, int angle1, int angle2, int cost){
	if(at->best != -1 && at->best < at->cost + cost){
		return;
	}
	at->best = at->cost + cost;

	auto dsts{ at->dst->calcValids(at, angle1, angle2) };
	for(auto dst : dsts){
		recurse(dst, angle1, angle2, at->best);
	}
}
int main(){
	int n, a1, a2, d;
	std::cin >> n >> d >> a1 >> a2;

	std::vector<junction*> juns(n + 1);
	for(int i = 1; i <= n; i++){
		juns[i] = new junction(i);
	}

	for(int i = 1; i <= n; i++){
		int m;
		std::cin >> m;
		for(int j = 0; j < m; j++){
			int t, s, a;
			std::cin >> t >> s >> a;
			juns[i]->connections.emplace_back(new connection(juns[i], juns[t], s, a));
		}
	}
	for(int i = 1; i <= n; i++){
		for(auto c : juns[i]->connections){
			c->calcExit();
		}
	}

	for(auto tpl : juns[1]->connections){
		recurse(tpl, a1, a2, 0);
	}
	std::vector<connection> ends{};
	for(auto to : juns[d]->connections){
		for(auto from : to->dst->connections){
			if(from->dst == juns[d] && from->best != -1){
				ends.emplace_back(*from);
			}
		}
	}

	for(auto j : juns){
		if(j){
			for(auto c : j->connections){
				if(c->dst != juns[d])
					c->best = -1;
			}
		}
	}

	for(auto to : juns[d]->connections){
		for(auto from : to->dst->connections){
			if(from->dst == juns[d] && from->best != -1){
				recurse(from, a1, a2, from->best - from->cost);
			}
		}
	}

	int min = 1000000000;
	for(auto to : juns[1]->connections){
		for(auto from : to->dst->connections){
			if(from->dst == juns[1]){
				if(from->best != -1){
					min = min > from->best ? from->best : min;
				}
			}
		}
	}

	if(min == 1000000000){
		std::cout << "impossible" << std::endl;
	} else{
		std::cout << min << std::endl;
	}
}