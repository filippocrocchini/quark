from shader import *
import re

blockRegex = re.compile(r"(\w*?)\s* (\[[^\].]*\])? \s* (?:\-\> \s* (\(.*?\))?)? \s*\< (.*?) \>\s*?", re.VERBOSE | re.DOTALL)

def parseBlock( blockMatch ):
    label = blockMatch.group(1)

    version = re.sub( r'\[|\]', r'', str(blockMatch.group(2)) )
    if version == "None":
        version = None

    output = re.sub( r'\(|\)', r'', str(blockMatch.group(3)) )
    if output == "None":
        output = None

    body = blockMatch.group(4)

    if label != None and body != None:
        body = re.findall('..*?\n', body)
        return Block(label, version, output, body)

    return None

def parseShaderFromFile( path ):
    f = open(path)
    shader = parseShader(f.read())
    f.close()
    return shader

def parseShader( text ):
    if not text:
        return None

    lines = [l.split('//')[0].strip() for l in text.split('\n') if len(l) > 0]
    lines = [l for l in lines if len(l)>0]
    blocks = {}
    block = None

    for blockCode in [l for l in re.finditer(blockRegex, '\n'.join(lines))]:
        block = parseBlock(blockCode)
        if block != None:
            blocks.update(block.list())

    if all(x in blocks for x in ["uniforms","attributes","vertex","fragment"]):
        return Shader(blocks.get("uniforms"),blocks.get("attributes"), blocks.get("vertex_output"),blocks.get("vertex"), blocks.get("fragment"))
    return None
