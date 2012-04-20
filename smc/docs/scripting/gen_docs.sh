#!/bin/bash

echo -n "Creating html/... directories... "
mkdir -p html/graphics
echo "Done."

echo -n "Copying graphics... "
cp "../../data/icon/window_32.png" "html/graphics"
cp "../../data/pixmaps/enemy/furball/brown/turn.png" "html/graphics/furball.png"
cp "../../data/pixmaps/enemy/eato/brown/3.png" "html/graphics/eato.png"
cp "../../data/pixmaps/enemy/flyon/orange/open_1.png" "html/graphics/flyon.png"
echo "Done."

echo "Converting Markdown files with kramdown."
for sourcefile in `ls *.md`; do
    targetfile=`echo $sourcefile | sed s/\.md/\.html/`
    echo "$sourcefile -> html/$targetfile"
    kramdown --toc-levels 2..3 --template template.html.erb $sourcefile > html/$targetfile
done
echo "Done."

echo -n "Copying stylesheet... "
cp style.css html
echo "Done."

echo "Finished."
exit 0