
# bcalc

[![Build Status](https://travis-ci.org/jb55/bcalc.svg)](https://travis-ci.org/jb55/bcalc)

  A simple calculator that understands Bitcoin Units

## Examples

  Basic example

    $ bcalc 1 msat + 2 sats + 3 bits in msats
    302001 msat

  BTC to satoshis

    $ bcalc 0.02 BTC
    2000000 sat

  satoshis to millisatoshis (for payment channels), also dont print unit

    $ bcalc --no-unit 100 sat in msats
    100000

  mBTC + bits to BTC

    $ bcalc 100 mBTC + 20 bits in btc
    0.10002 BTC

  Division

    $ bcalc 1 BTC / 100 in bits
    10000 bits

  Multiplication

    $ bcalc '10 mbtc * 30 in bits'
    300000 bits

  Fiat currencies

    $ bcalc --price 20000 30 usd in bits
    1500 bits

    $ bcalc --price 16000 780 bits in fiat
    12.48 usd

  The Bitcoin pizzas

    $ bcalc --price 0.0041 41 usd in btc
    10000 BTC

## Install

    $ make install

## Units

  - BTC,
  - mBTC (milli-bitcoin),
  - bits (μBTC, micro-bitcoin),
  - finney,
  - satoshi (sat),
  - millisatoshi (msat),
