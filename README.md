
# bcalc

[![Build Status](https://travis-ci.org/jb55/bcalc.svg)](https://travis-ci.org/jb55/bcalc)

  A simple calculator that understands Bitcoin Units

## Examples

  Basic example

    $ bcalc --msat 1 msat + 2 sats + 3 bits
    302001 msat

  BTC to satoshis

    $ bcalc 0.02 BTC
    2000000 sat

  satoshis to millisatoshis (for payment channels)

    $ bcalc --no-unit --msat 100 sat
    100000

  mBTC + bits to BTC

    $ bcalc --btc 100 mBTC + 20 bits
    0.10002 BTC

  Division

    $ bcalc --bits 1 BTC / 100
    10000 bits

  Multiplication

    $ bcalc -b '10 mbtc * 30'
    300000 bits

  Fiat currencies

    $ bcalc --price 20000 --bits 30 usd
    1500 bits

    $ bcalc --price 16000 --usd 780 bits
    12.48 usd

  The Bitcoin pizza

    $ bcalc --price 0.0041 --btc 41 usd
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
