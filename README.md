#ESP-WROOM-02 [ARECX6](https://www.arecx6.jp/) HealthCheck Program.
====

##Overview
ESP-WROOM-02を使った、6チャンネルワンセグ24時間録画機[ARECX6](https://www.arecx6.jp/)の録画状態を監視して再起動を行う機材

[ARECX6](https://www.arecx6.jp/)の動作が不安定で録画が停止していることがあるために作成

## Description

ESP-WROOM-02から[ARECX6](https://www.arecx6.jp/)を（２分おきに）監視し、録画状態でない場合にARECX6を再起動、その後録画開始する単純なプログラムです。

## Requirement

-ESP-WROOM-02
-[ARECX6](https://www.arecx6.jp/)([Firmware 3.03](http://www.arecx6.jp/download/index.html))のみ検証

## Install

	$ git clone https://github.com/ripjyr/ESP-WROOM-02-ARECX6-HealthCheck

## License

[MIT](http://b4b4r07.mit-license.org)

## Author

[ripjyr](https://github.com/ripjyr)
