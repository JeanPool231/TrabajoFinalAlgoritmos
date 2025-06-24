#ifndef __HASHENTIDAD_H__
#define __HASHENTIDAD_H__

class HashEntidad {
private:
	int key;
	int value;
public:
	HashEntidad(int key, int value) {
		this->key = key;
		this->value = value;
	}
	int getKey() { return key; }
	int getValue() { return value; }
};

#endif // !__HASHENTIDAD_H__