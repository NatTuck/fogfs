
sudo apt-get install -y \
     build-essential pkg-config checkinstall libbsd-dev libfuse-dev \
     libxdg-basedir-dev ninja-build meson

SODIUM=libsodium-1.0.12
wget -c https://download.libsodium.org/libsodium/releases/$SODIUM.tar.gz
tar xzvf $SODIUM.tar.gz
cd $SODIUM
./configure
make
sudo checkinstall -y --nodoc --pkgname libsodium
cd ..

TOML=toml-v0.4.0
wget -c https://github.com/skystrife/cpptoml/archive/$TOML.tar.gz
tar xzvf $TOML.tar.gz
sudo cp cpp*$TOML/include/* /usr/local/include

