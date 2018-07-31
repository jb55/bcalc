
# bcalc

[![Build Status](https://travis-ci.org/jb55/bcalc.svg)](https://travis-ci.org/jb55/bcalc)

  A simple calculator that understands Bitcoin Units

## Examples

  Basic example

    $ bcalc 1 msat + 2 sats + 3 bits to msats
    302001 msats

  BTC to satoshis

    $ bcalc 0.02 BTC
    2000000 sats

  satoshis to millisatoshis (for payment channels), also dont print unit

    $ bcalc --no-unit 100 sat to msats
    100000

  mBTC + bits to BTC

    $ bcalc 100 mBTC + 20 bits to btc
    0.10002 BTC

  Division

    $ bcalc 1 BTC / 100 to bits
    10000 bits

  Multiplication

    $ bcalc '10 mbtc * 30 to bits'
    300000 bits

  Fiat currencies

    $ bcalc --price 20000 30 usd to bits
    1500 bits

    $ bcalc --price 16000 780 bits to fiat
    12.48 usd

  The Bitcoin pizzas

    $ bcalc --price 0.0041 41 usd to btc
    10000 BTC

## Install

  If on Ubuntu, check you have the prerequisites to build this package

    $ sudo apt-get install build-essential bison flex

  Build and install

    $ make install

  If you run into errors because your user doesn't have write access to /usr/local/bin then

    $ sudo make install

## Units

  - BTC,
  - mBTC (milli-bitcoin),
  - bits (μBTC, micro-bitcoin),
  - finney,
  - satoshi (sat),
  - millisatoshi (msat),
