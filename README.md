#[ESP-WROOM-02](http://amzn.to/2i9bEur) [ARECX6](https://www.arecx6.jp/) HealthCheck Program.
====

##Overview
[ESP-WROOM-02](http://amzn.to/2i9bEur)を使った、6チャンネルワンセグ24時間録画機[ARECX6](https://www.arecx6.jp/)の録画状態を監視して再起動を行う機材  
[ARECX6](https://www.arecx6.jp/)の動作が不安定で録画が停止していることがあるために作成

## Description

[ESP-WROOM-02](http://amzn.to/2i9bEur)から[ARECX6](https://www.arecx6.jp/)を（２分おきに）監視し、録画状態でない場合にARECX6を再起動、その後録画開始する単純なプログラムです。  
[Windows/ARecX6 - cubic9.com](http://cubic9.com/Windows/ARecX6/)のESP-WROOM-02版

## Requirement

* [ESP-WROOM-02](http://amzn.to/2i9bEur)
* [ARECX6](https://www.arecx6.jp/)([Firmware 3.03](http://www.arecx6.jp/download/index.html))のみ検証
* 2.4Ghz Wi-Fiルーター（[ESP-WROOM-02](http://amzn.to/2i9bEur)が2.4Ghzのみのため）

## Install

	$ git clone https://github.com/ripjyr/ESP-WROOM-02-ARECX6-HealthCheck

## License

[MIT](http://b4b4r07.mit-license.org)

## Author

[ripjyr](https://github.com/ripjyr)
