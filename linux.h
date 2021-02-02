#ifndef LINUX_H
#define LINUX_H

#define clock_gettime_nsec_np(CID) \
        (unsigned long long)((double)clock() / CLOCKS_PER_SEC * 1000000000L)
#define mlx_mouse_move(a, b, c) mlx_mouse_move(p->mlx, a, b, c)
#define mlx_mouse_hide() mlx_mouse_hide(p.mlx, p.win)

#endif