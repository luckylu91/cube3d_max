##Cube3d pour max

**packages a installer** (ça peut prendre un peu de place, tu peux désinstaller plus tard avec remove et autoremove):
  * `sudo apt install gcc make xorg libxext-dev libbsd-dev`

pour la suite je suppose que tu es dans cube3d_max/ (avec cd)

**compiler minilibx pour générer libmlx.a et le mettre dans le repertoire racine (cube3d_max):**
  * `cd minilibx-linux-master`
  * `./configure`
  * `cp libmlx.a ..`
  * `cd ..`

**compiler libft et printf:**
  * `make libft`
  * `make printf`

**enfin, compiler l'executable "render":**
  * `make render`

**pour l'éxécuter:**
  * `./render`
