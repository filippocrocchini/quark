import sys

class Block:
    def __init__(self, label, version, output, body):
        self.label = label
        self.version = version
        self.output = output
        self.body = body

    def list(self):
        return {self.label : self}

    def __str__(self):
        return "Block< Label: '" + str(self.label) + "', Body: '" + str(self.body) + "' Version: '" + str(self.version) + "', Output:'" + str(self.output) + "' >"

class Shader:
    def __init__(self,uniforms, attributes,  vertex_out, vertex, fragment):
        self.vertex = vertex
        self.fragment = fragment
        self.uniforms = uniforms
        self.attributes = attributes
        self.vertex_out = vertex_out

    def getVertexSource(self):
        source = ''

        if self.vertex.version:
            source += '#version ' + self.vertex.version + '\n\n'

        source += ''.join("uniform " + str(l) for l in self.uniforms.body) + '\n'
        source += ''.join("in " + str(l) for l in self.attributes.body) + '\n'
        if self.vertex.output:
            source += ''.join("out " + str(l).strip() + ";\n" for l in self.vertex.output.split(',')) + '\n'

        if self.vertex_out:
            source += "out VertexOutput {\n" + ''.join("   " + str(l) for l in self.vertex_out.body) + "} vertex_output;\n\n"
        source += ''.join("" + str(l) for l in self.vertex.body) + '\n'
        return source

    def getFragmentSource(self):
        source = ''

        if self.fragment.version:
            source += '#version ' + self.fragment.version + '\n\n'

        source += ''.join("uniform " + str(l) for l in self.uniforms.body) + '\n'

        if self.vertex.output:
            source += ''.join("in " + str(l).strip() + ";\n" for l in self.vertex.output.split(',')) + '\n'

        if self.fragment.output:
            source += ''.join("out " + str(l).strip() + ";\n" for l in self.fragment.output.split(',')) + '\n'
        else:
            source += "out vec4 gl_FragColor;\n\n"

        if self.vertex_out:
            source += "in VertexOutput {\n" + ''.join("   " + str(l) for l in self.vertex_out.body) + "} vertex_output;\n\n"
        source += ''.join("" + str(l) for l in self.fragment.body) + '\n'
        return source
