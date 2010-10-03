all: node

node: node-v0.2.2.tar.gz
	cd node-v0.2.2 && ./configure && make && cp node ../
node-v0.2.2.tar.gz:
	wget http://nodejs.org/dist/node-v0.2.2.tar.gz
	tar -xvf node-v0.2.2.tar.gz