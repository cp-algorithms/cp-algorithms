<?php

require_once dirname(__FILE__) . '/markdown/MarkdownExtra.inc.php';

processDirectory('src', 'target');

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
        if ($file[0] < 'A') {
            continue;
        }
        $srcFile = "$src/$file";
        $dstFile = "$dst/$file";
        if (!is_dir($srcFile)) {
            if (preg_match('/.*\.txt/i', $file)) {
                convertFile($srcFile, $dstFile);
            }
        } else {
            processDirectory($srcFile, $dstFile);
        }
    }
}

function convertFile($src, $dst) {
    $text = file_get_contents($src);
    $html = \Michelf\MarkdownExtra::defaultTransform($text);
    file_put_contents($dst, $html);
}