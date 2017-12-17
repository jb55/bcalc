
# bcalc

  A simple calculator that understands Bitcoin Units

## Examples

  Basic example

    $ bcalc --msat -p <<<'1 msat + 2 sats + 3 bits'
    302001 msat

  BTC to satoshis

    $ bcalc -p <<<'0.02 BTC'
    2000000 sat

  satoshis to millisatoshis (for payment channels)

    $ bcalc --msat <<<'100 sat'
    100000

  mBTC + bits to BTC

    $ bcalc -p --btc <<<'100 mBTC + 20 bits'
    0.10002 BTC

## Install

    $ make install

## Units

  - BTC,
  - mBTC (milli-bitcoin),
  - bits (μBTC, micro-bitcoin),
  - finney,
  - satoshi (sat),
  - millisatoshi (msat),
