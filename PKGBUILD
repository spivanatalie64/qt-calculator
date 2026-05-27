# Maintainer: Natalie <natalie@acreetionos.org>
pkgname=qt-calculator
pkgver=1.0.0
pkgrel=1
pkgdesc="A streamlined Qt6 calculator application for AcreetionOS"
arch=('x86_64')
url="https://acreetionos.org"
license=('GPL3')
depends=('qt6-base')
makedepends=('cmake')
source=('main.cpp'
        'CMakeLists.txt')
sha256sums=('SKIP'
            'SKIP')

build() {
  cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/usr
  cmake --build build
}

package() {
  DESTDIR="${pkgdir}" cmake --install build
  mv "${pkgdir}/usr/bin/QtCalculator" "${pkgdir}/usr/bin/qt-calculator"
}
