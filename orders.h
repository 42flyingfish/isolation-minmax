#ifndef ORDERS_H
#define ORDERS_H

struct Orders {
	int move;
	int weight;

	bool operator<(const Orders & other) const {
		return weight < other.weight;
	}
};

#endif
