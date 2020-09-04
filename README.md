# WARNING: Abandoned, archived
This project is obsolete. GMail changed multiple times and this project doesn't makes sense anymore.

# GMail Auto Clicker

It's a simple auto-clicker for GMail "Check mail now" button.

## Why

I use GMail interface for my private account through its wonderful feature "Check mail from other accounts".
However GMail checks my mail in random time. I hate to wait for 1+ hour for my mails to sync.

GMail interface offers a button "Check mail now", but I can't just sit and click it every 2 minutes. That's why I wrote *GMail Auto Clicker*.

## How it works

GMAC (GMail Auto Clicker) uses integrated QT Webkit browser. It expects you to:
* login to your account (as you usually do on your beloved browser),
* navigate to a page that contains "Check mail now" button (it's *Settings -> Accounts*)
* when GMAC detects "Check mail now" button on a page it automagically "clicks" it,
* it repeats "clicking" every 3 minutes,

# How to



# Internals

## Why this way

I'm sure there are better ways to do it, but this one is simple and it works ;)

Using some call-API-like script was not that easy, because:
* we need to login to GMail anyway (so store password in safe place, keep session etc.)
* google code is obfuscated and may change faster than GUI
* google ajax calls are not really obvious (a lot of fields in requests and magic info)

## Is it safe ?

GMAC includes QT5 webkit browser. So it uses full set of features implemented in webkit.
It doesn't store your passwords. It does not connect to anything else than google.com servers. It caches nothing on your HDD.
It's open-source, you can check how it works.

## Known issues
It's not a commercial product - just a simplest code possible, so don't expect too much. If you want to make it better - please participate :)

* GMAC checks mail every 3 minutes, and it lacks a configuration option for changing that time,
* it takes a lot of memory - because all webkit cache is stored in RAM
* there is some bug in QT5 webkit, which takes a lot of CPU for some of google subpages. To avoid that, just make a GMAC window small as possible - it will free your CPU then.
