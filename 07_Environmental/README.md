Installation
============

Build Prerequisites
-------------------
  - [LibRHash Library](https://github.com/rhash/RHash/blob/master/docs/LIBRHASH.md)
  - Meson Build system
  - Git
  - (optionally) [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/readline.html#SEC23)


Build and install
-----------------
Download and install LibRHash
```sh
git clone https://github.com/rhash/RHash.git
cd RHash
./configure --enable-lib-static
sudo make install install-lib-so-link
```

Run Meson
```sh
meson setup buliddir
cd builddir
ninja
```

Build with Readline
-----------------
Download and install GNU Readline
```sh
wget http://git.savannah.gnu.org/cgit/readline.git/snapshot/readline-master.tar.gz
tar -xzf readline-master.tar.gz
cd readline-master
./configure && sudo make install
```

Configure Meson build
```sh
meson setup buliddir
cd builddir
meson confgiure -Dwith_readline=true
ninja
```

Run tests
-----------------
Compare rhasher output with md5sum and sha1sum.
```sh
cd builddir
ninja tests
```

Clean all
-----------------
```sh
rm -r builddir
cd RHash && sudo make unistall
cd readline-master && sudo make unistall
```