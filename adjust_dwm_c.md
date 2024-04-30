dwm
---

##### disable focus-follow-mouse

in dwm.c comment out

```c
178  static void enternotify(XEvent *e);
```
```c
276  [EnterNotify] = enternotify
```


##### dump little squares in tags

in dwm.c comment out

```c
838  if (occ & 1 << i)
	    drw_rect(drw, x + boxs, boxs, boxw, boxw,
		    m == selmon && selmon->sel && selmon->sel->tags & 1 << i,
		    urg & 1 << i);
```

