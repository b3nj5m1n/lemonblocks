<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <h3 align="center">lemonblocks</h3>

  <p align="center">
    A status bar generator for lemonbar, inspired by i3blocks and dwmblocks.
    <br />
    <br />
    <a href="https://github.com/b3nj5m1n/lemonblocks/issues">Report Bug</a>
    ·
    <a href="https://github.com/b3nj5m1n/lemonblocks/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
* [Contributing](#contributing)
* [License](#license)



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]]()

A status bar generator for lemonbar, inspired by i3blocks and dwmblocks, written in plain C.

![demo](https://i.imgur.com/VEPfM47.gif)

![demo](https://i.imgur.com/NkMaIH8.png)

Lemonbar reads from stdin for the status, it supports clickable areas, the commands will be written to stout.

Lemonblocks tries to make feeding the bar easier. You can define your own modules which you can asign signals. Every time you want to update one of your modules, you can send a signal to the instance of lemonblocks to run the associated command. This means that you don't have to run a script at certain intervals, instead you update it only when necessary.


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

* lemonbar 
Lemonbar is a very leightweight bar. The original doesn't support XFT fonts, for that you will have to use a fork, such as [this one](https://aur.archlinux.org/packages/lemonbar-xft-git/), but if you want to have emojis you should probably use [this fork](https://github.com/freundTech/bar).
*   (Optional) [Ubuntu Mono Font](https://aur.archlinux.org/packages/nerd-fonts-ubuntu-mono/)
*   (Optional) [Twemoji Font (Twitters emojis)](https://aur.archlinux.org/packages/ttf-twemoji/)

### Installation

1. Clone the repo
```sh
git clone https://github.com/b3nj5m1n/lemonblocks.git
```
2. Bulid & Install lemonblocks
```sh
sudo make install
```
3. Copy default config
```sh
make config
```
4. Copy scripts
```sh
sudo make scripts
```

<!-- USAGE EXAMPLES -->
## Usage

### Starting lemonbar & lemonblocks

The script called start.sh will start lemonbar with sensible default settings as well as lemonblocks.

The script is moved to /usr/bin when installing, you can call it like this:
```bash
start-lemonbar.sh &
```

### Updating a module

```bash
# 3 is the signal for your module
pkill lemonblocks -3
```

### Config

You can configure your modules in the file config.txt located at ~/.config/lemonblocks. (Run make config to create the directory and copy the default config)
```c
# Seperate values with a , (No space afterwards)
# Interval  Signal Icon  Command Alignment   Initial Status  BgColor FgColor LeftClick   MiddleClick RightClick  ScrollUp    ScrollDown Prefix Suffix
# Interval of 0 means it will only be updated by signals. NULL means nothing or default value for icons, colors and mouse events
# Example config:
0,3,🍍,/usr/bin/lbscripts/powermenu.sh,l, ,NULL,f8f8ff,NULL,NULL,NULL,NULL,NULL,[,]
1,4,NULL,/usr/bin/lbscripts/bspwm.sh,l, ,NULL,f8f8ff,NULL,NULL,NULL,NULL,NULL,[,]
1,5,NULL,/usr/bin/lbscripts/cmus.sh,l, ,NULL,f8f8ff,cmus-remote -u; pkill lemonblocks -5,NULL,NULL,cmus-remote -v +1%,cmus-remote -v -1%,[,]
0,6,🔈,/usr/bin/lbscripts/volume.sh,r, ,aa1d1f21,f8f8ff,amixer set Master toggle; pkill lemonblocks -6,NULL,NULL,amixer -q sset Master 1%+; pkill lemonblocks -6,amixer -q sset Master 1%-; pkill lemonblocks -6,[,]
0,7,📁,/usr/bin/lbscripts/free-space.sh,r, ,aa1d1f21,f8f8ff,NULL,NULL,NULL,NULL,NULL,[,]
0,8,🐒,/usr/bin/lbscripts/layout.sh,r, ,aa1d1f21,f8f8ff,NULL,NULL,NULL,NULL,NULL,[,]
300,10,NULL,/usr/bin/lbscripts/network.sh,r, ,aa1d1f21,f8f8ff,NULL,NULL,NULL,NULL,NULL,[,]
30,11,⏰,/usr/bin/lbscripts/date.sh,r, ,aa1d1f21,f8f8ff,NULL,NULL,NULL,NULL,NULL,[,]
```


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/b3nj5m1n/lemonblocks?style=flat-square
[contributors-url]: https://github.com/b3nj5m1n/b3nj5m1n/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/b3nj5m1n/lemonblocks.svg?style=flat-square
[forks-url]: https://github.com/b3nj5m1n/lemonblocks/network/members
[stars-shield]: https://img.shields.io/github/stars/b3nj5m1n/lemonblocks.svg?style=flat-square
[stars-url]: https://github.com/b3nj5m1n/lemonblocks/stargazers
[issues-shield]: https://img.shields.io/github/issues/b3nj5m1n/lemonblocks.svg?style=flat-square
[issues-url]: https://github.com/b3nj5m1n/lemonblocks/issues
[license-shield]: https://img.shields.io/github/license/b3nj5m1n/lemonblocks.svg?style=flat-square
[license-url]: https://github.com/b3nj5m1n/lemonblocks/blob/master/LICENSE.txt
[product-screenshot]: https://socialify.git.ci/b3nj5m1n/lemonblocks/image?font=Inter&language=1&owner=1&pattern=Circuit%20Board&theme=Light
