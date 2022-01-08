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