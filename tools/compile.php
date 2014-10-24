<?php

require_once dirname(__FILE__) . '/markdown/MarkdownExtra.inc.php';

processDirectory('src', 'target');

echo "\nDONE: site should be accessible at\n    " . rootPath() . "/index.html\n";

function processDirectory($src, $dst) {
    echo "Processing directory: $src -> $dst\n";
    $dir = opendir($src);
    if ($dir === false) {
        echo "Could not open directory: $src";
        return;
    }
    if (!file_exists($dst)) {
        mkdir($dst);
    }
    while (true) {
        $file = readdir($dir);
        if ($file === false) {
            break;
        }
        if ($file[0] == '.' || $file[0] == '_') {
            continue;
        }
        $srcFile = "$src/$file";
        $dstFile = "$dst/$file";
        if (!is_dir($srcFile)) {
            if (preg_match('/.*\.(txt|md)/i', $file)) {
                convertFile($srcFile, $dstFile);
            } else {
                copy($srcFile, $dstFile);
            }
        } else {
            processDirectory($srcFile, $dstFile);
        }
    }
}

function convertFile($src, $dst) {
    $text = file_get_contents($src);
    $params = extractParams($text);
    $params['text'] = \Michelf\MarkdownExtra::defaultTransform($text);
    $html = loadTemplate($params['template'], $params);
    $dst = str_replace(array('.txt', '.md'), '.html', $dst);
    file_put_contents($dst, $html);
}

function extractParams(&$text) {
    $vars = array('template' => 'default', 'root' => rootPath());
    $lines = explode("\n", $text);
    $res = array();
    foreach ($lines as $line) {
        $matches = array();
        if (preg_match('/^\s*\<\!\-\-\?([a-z]+)\s+(.*)\-\-\>\s*$/', $line, $matches)) {
            $vars[$matches[1]] = $matches[2];
            continue;
        }
        $res[] = $line;
    }
    $text = implode("\n", $res);
    return $vars;
}

function loadTemplate($name, $params) {
    $template = file_get_contents("src/_templates/$name.html");
    foreach ($params as $name => $value) {
        $template = str_replace("&$name&", $value, $template);
    }
    return $template;
}

function rootPath() {
    global $argv;
    if (count($argv) < 2) {
        $path = realpath('target');
    } else {
        $path = $argv[1];
    }
    if ($path[1] == ':') { // windows path with drive letter
        $path = '/' . str_replace('\\', '/', $path);
    }
    if (substr($path, 0, 5) != 'http:') {
        $path = 'file://' . $path;
    }
    return "$path";
}

