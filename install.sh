echo "Setting up environment"
sh environment.sh
echo "Installing the game"
sudo make install
make clean
echo "Game installed"
echo "Type 'katw' to play it"
