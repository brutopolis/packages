name ferawc
version 0.0.1
description "ferawc install script"
setup()
{
    rm -rf feraw
    git clone https://github.com/brutopolis/feraw
    cd feraw
    rm -rf /usr/local/bin/ferawc
    {                                        
        head -n1 ferawc                                                                 
        printf "FERAW_JS_FILE='"
        sed "s/'/'\\\\''/g" feraw.js  # Escapa aspas simples
        echo "'"
        tail -n +2 ferawc  
    } > /usr/local/bin/ferawc
    chmod +x /usr/local/bin/ferawc
}