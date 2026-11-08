<?xml version="1.0" encoding="UTF-8"?>
<!--
MIT License

Copyright (c) 2022 Julien Moura (In Geo Veritas)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-->
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:atom="http://www.w3.org/2005/Atom"
    xmlns:dc="http://purl.org/dc/elements/1.1/">

    <xsl:output method="html" encoding="UTF-8" indent="yes"/>

    <xsl:template match="/">
        <html>
            <head>
                <meta charset="UTF-8"/>
                <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
                <title>
                    <xsl:value-of select="rss/channel/title"/>
                </title>
                <style>

*, *::before, *::after {
  box-sizing: border-box;
}

body {
  font-family: system-ui, -apple-system, BlinkMacSystemFont, sans-serif;
  max-width: 900px;
  margin: 0 auto;
  padding: 20px 16px;
  background: #f9fafb;
  color: #111827;
}

header {
  border-bottom: 2px solid #e5e7eb;
  padding-bottom: 20px;
  margin-bottom: 30px;
}

header img {
  vertical-align: middle;
  margin-right: 15px;
}
header .meta {
  margin-top: 15px;
  font-size: 0.9em;
  color: #6b7280;
}

h1 {
  margin: 0;
  font-size: clamp(1.2rem, 5vw, 1.8rem);
  word-break: break-word;
}

.item {
  background: white;
  padding: 20px;
  margin-bottom: 25px;
  border-radius: 10px;
  box-shadow: 0 4px 12px rgba(0,0,0,0.05);
}

.item h2 {
  margin-top: 0;
  font-size: clamp(1rem, 4vw, 1.3rem);
  word-break: break-word;
}

.meta {
  font-size: 0.9em;
  color: #6b7280;
  margin-bottom: 10px;
}

.categories span {
  background: #eef2ff;
  border-radius: 6px;
  color: #3730a3;
  display: inline-block;
  font-size: 0.75em;
  margin-right: 5px;
  padding: 3px 8px;
}

.item img {
  border-radius: 8px;
  display: block;
  height: auto;
  margin: 15px 0;
  width: 100%;
}

a {
  color: #2563eb;
  text-decoration: none;
  word-break: break-word;
}

a:hover {
  text-decoration: underline;
}
                </style>
            </head>

            <body>

                <header>
                    <xsl:if test="rss/channel/image/url">
                        <img>
                            <xsl:attribute name="src">
                                <xsl:value-of select="rss/channel/image/url"/>
                            </xsl:attribute>
                            <xsl:attribute name="width">64</xsl:attribute>
                        </img>
                    </xsl:if>

                    <h1>
                        <xsl:value-of select="rss/channel/title"/>
                    </h1>

                    <p>
                        <xsl:value-of select="rss/channel/description"/>
                    </p>

                    <p>
                        <a>
                            <xsl:attribute name="href">
                                <xsl:value-of select="rss/channel/link"/>
                            </xsl:attribute>
      Visit website
                        </a>
                    </p>
                    <div class="meta">

                        <xsl:if test="author">
    By <xsl:value-of select="author"/>
                        </xsl:if>

                        <xsl:if test="pubDate">
    —                            <strong>Published:</strong>
                            <xsl:value-of select="pubDate"/>
                        </xsl:if>

                        <xsl:if test="updated">
    —                            <strong>Updated:</strong>
                            <xsl:value-of select="updated"/>
                        </xsl:if>

                    </div>
                </header>

                <xsl:for-each select="rss/channel/item">

                    <div class="item">

                        <h2>
                            <a>
                                <xsl:attribute name="href">
                                    <xsl:value-of select="link"/>
                                </xsl:attribute>
                                <xsl:value-of select="title"/>
                            </a>
                        </h2>

                        <div class="meta">
                            <xsl:if test="author">
      Par <xsl:value-of select="author"/>
                            </xsl:if>
                            <xsl:if test="pubDate">
      —                                <xsl:value-of select="pubDate"/>
                            </xsl:if>
                        </div>

                        <!-- Image si enclosure image/* -->
                        <xsl:if test="enclosure[starts-with(@type,'image/')]">
                            <img>
                                <xsl:attribute name="src">
                                    <xsl:value-of select="enclosure/@url"/>
                                </xsl:attribute>
                            </img>
                        </xsl:if>

                        <p>
                            <xsl:value-of select="description"/>
                        </p>

                        <div class="categories">
                            <xsl:for-each select="category">
                                <span>
                                    <xsl:value-of select="."/>
                                </span>
                            </xsl:for-each>
                        </div>

                    </div>

                </xsl:for-each>

            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
