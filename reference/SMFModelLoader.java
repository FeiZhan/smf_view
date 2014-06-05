
/*
  Copyright (c) 2004, Bradley Jones
  All rights reserved.

  Redistribution and use in source and binary forms, with or without 
  modification, are permitted provided that the following conditions are
  met:

    * Redistributions of source code must retain the above copyright notice, 
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the nondot.org nor the names of its contributors may 
      be used to endorse or promote products derived from this software without
      specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
  POSSIBILITY OF SUCH DAMAGE.
*/
package org.nondot.mesh;

import java.io.*;
import java.util.*;

/**
 * This class loads the SMF model format
 */
public class SMFModelLoader {
  MeshBuilder meshBuilder;
  
  public SMFModelLoader(MeshBuilder mb) {
    meshBuilder = mb;
  }
  
  public Mesh load(InputStream is) throws IOException {
    BufferedReader br = new BufferedReader(new InputStreamReader(is));
    meshBuilder.startMesh();
    
    String line = br.readLine();
    while(line != null) {
      if(line.startsWith("v")) {
        readVertex(line);
      }
      else if(line.startsWith("f")) {
        readFace(line);
      }
      else {
        System.out.println("Unknown Line: " + line);
      }
      line = br.readLine();
    }
    
    meshBuilder.endMesh();
    return meshBuilder.getMesh();
  }
  
  private void readVertex(String line) throws IOException {
    StringTokenizer st = new StringTokenizer(line);
    if(st.countTokens() != 4) {
      throw new IOException("Bad SMF line: " + line);
    }
    
    String v = st.nextToken();
    if(v.compareTo("v") != 0) {
      throw new IOException("Bad SMF line: " + line);
    }
    
    float x = Float.parseFloat(st.nextToken());
    float y = Float.parseFloat(st.nextToken());
    float z = Float.parseFloat(st.nextToken());
    
    meshBuilder.addVertex(x,y,z);
  }
  
  private void readFace(String line) throws IOException {
    StringTokenizer st = new StringTokenizer(line);
    if(st.countTokens() != 4) {
      throw new IOException("Bad SMF line: " + line);
    }
  
    String f = st.nextToken();
    if(f.compareTo("f") != 0) {
      throw new IOException("Bad SMF line: " + line);
    }
    
    int v0 = Integer.parseInt(st.nextToken()) - 1;
    int v1 = Integer.parseInt(st.nextToken()) - 1;
    int v2 = Integer.parseInt(st.nextToken()) - 1;
    
    meshBuilder.addFace(v0,v1,v2);
  }
}
