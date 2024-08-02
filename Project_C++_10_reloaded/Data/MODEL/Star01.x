xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 98;
 -0.00006;3.60069;1.20792;,
 -1.33182;1.33146;0.00012;,
 0.00012;1.35579;1.30749;,
 -1.20813;3.60078;-0.00006;,
 -1.20813;3.60078;-0.00006;,
 -0.00027;1.35573;-1.30764;,
 -1.33182;1.33146;0.00012;,
 -0.00036;3.60072;-1.20828;,
 1.33146;1.33176;-0.00021;,
 1.20789;3.60069;-0.00024;,
 1.20789;3.60069;-0.00024;,
 1.33146;1.33176;-0.00021;,
 -0.00021;5.50407;0.92427;,
 -0.92487;5.50386;-0.00027;,
 -0.92487;5.50386;-0.00027;,
 -0.00042;5.50401;-0.92493;,
 0.92427;5.50386;-0.00021;,
 0.92427;5.50386;-0.00021;,
 -0.00027;6.77583;0.49998;,
 -0.50055;6.77565;-0.00033;,
 -0.50055;6.77565;-0.00033;,
 -0.00039;6.77586;-0.50073;,
 0.50022;6.77580;-0.00045;,
 0.50022;6.77580;-0.00045;,
 -0.00024;7.44552;-0.00033;,
 -0.00024;7.44552;-0.00033;,
 3.60075;0.00036;1.20780;,
 1.35558;0.00027;1.30746;,
 3.60069;1.20813;-0.00024;,
 3.60069;1.20813;-0.00024;,
 1.35546;-0.00003;-1.30770;,
 3.60066;0.00006;-1.20813;,
 1.33176;-1.33164;0.00003;,
 3.60081;-1.20798;-0.00018;,
 3.60081;-1.20798;-0.00018;,
 1.33176;-1.33164;0.00003;,
 5.50401;0.00018;0.92424;,
 5.50395;0.92478;-0.00036;,
 5.50395;0.92478;-0.00036;,
 5.50401;0.00015;-0.92490;,
 5.50410;-0.92445;-0.00027;,
 5.50410;-0.92445;-0.00027;,
 6.77592;0.00027;0.49998;,
 6.77583;0.50046;-0.00036;,
 6.77583;0.50046;-0.00036;,
 6.77580;0.00027;-0.50076;,
 6.77592;-0.49995;-0.00042;,
 6.77592;-0.49995;-0.00042;,
 7.44573;0.00024;-0.00054;,
 7.44573;0.00024;-0.00054;,
 -3.60054;0.00003;1.20822;,
 -1.33176;-1.33155;0.00006;,
 -1.35552;0.00006;1.30773;,
 -3.60078;-1.20810;0.00027;,
 -3.60078;-1.20810;0.00027;,
 -1.35594;0.00003;-1.30743;,
 -1.33176;-1.33155;0.00006;,
 -3.60087;-0.00015;-1.20786;,
 -3.60090;1.20801;0.00021;,
 -3.60090;1.20801;0.00021;,
 -5.50389;-0.00006;0.92496;,
 -5.50401;-0.92475;0.00036;,
 -5.50401;-0.92475;0.00036;,
 -5.50410;-0.00036;-0.92412;,
 -5.50416;0.92451;0.00027;,
 -5.50416;0.92451;0.00027;,
 -6.77568;-0.00021;0.50085;,
 -6.77592;-0.50067;0.00048;,
 -6.77592;-0.50067;0.00048;,
 -6.77580;-0.00021;-0.49989;,
 -6.77580;0.50022;0.00039;,
 -6.77580;0.50022;0.00039;,
 -7.44573;-0.00009;0.00027;,
 -7.44573;-0.00009;0.00027;,
 0.00006;-3.60054;1.20813;,
 0.00018;-1.35552;1.30758;,
 1.20825;-3.60075;0.00015;,
 1.20825;-3.60075;0.00015;,
 0.00000;-1.35552;-1.30752;,
 -0.00006;-3.60069;-1.20789;,
 -1.20798;-3.60066;0.00024;,
 -1.20798;-3.60066;0.00024;,
 0.00033;-5.50398;0.92496;,
 0.92478;-5.50362;0.00018;,
 0.92478;-5.50362;0.00018;,
 0.00018;-5.50398;-0.92454;,
 -0.92436;-5.50383;0.00024;,
 -0.92436;-5.50383;0.00024;,
 0.00030;-6.77562;0.50067;,
 0.50058;-6.77571;0.00015;,
 0.50058;-6.77571;0.00015;,
 0.00021;-6.77562;-0.50007;,
 -0.50019;-6.77586;0.00027;,
 -0.50019;-6.77586;0.00027;,
 0.00015;-7.44552;0.00036;,
 0.00015;-7.44552;0.00036;,
 -0.00018;-0.00006;-1.37526;,
 0.00006;0.00012;1.37526;;
 
 128;
 3;0,1,2;,
 3;3,1,0;,
 3;4,5,6;,
 3;7,5,4;,
 3;7,8,5;,
 3;9,8,7;,
 3;0,2,10;,
 3;10,2,11;,
 3;12,3,0;,
 3;13,3,12;,
 3;14,7,4;,
 3;15,9,7;,
 3;15,7,14;,
 3;16,9,15;,
 3;12,0,17;,
 3;17,0,10;,
 3;18,13,12;,
 3;19,13,18;,
 3;20,15,14;,
 3;21,15,20;,
 3;21,16,15;,
 3;22,16,21;,
 3;18,12,23;,
 3;23,12,17;,
 3;24,18,23;,
 3;24,19,18;,
 3;25,22,21;,
 3;25,21,20;,
 3;26,11,27;,
 3;28,11,26;,
 3;29,30,8;,
 3;31,30,29;,
 3;31,32,30;,
 3;33,32,31;,
 3;26,27,34;,
 3;34,27,35;,
 3;36,28,26;,
 3;37,28,36;,
 3;38,31,29;,
 3;39,33,31;,
 3;39,31,38;,
 3;40,33,39;,
 3;36,26,41;,
 3;41,26,34;,
 3;42,37,36;,
 3;43,37,42;,
 3;44,39,38;,
 3;45,39,44;,
 3;45,40,39;,
 3;46,40,45;,
 3;42,36,47;,
 3;47,36,41;,
 3;48,42,47;,
 3;48,43,42;,
 3;49,46,45;,
 3;49,45,44;,
 3;50,51,52;,
 3;53,51,50;,
 3;54,55,56;,
 3;57,6,55;,
 3;57,55,54;,
 3;58,6,57;,
 3;50,52,59;,
 3;59,52,1;,
 3;60,53,50;,
 3;61,53,60;,
 3;62,57,54;,
 3;63,57,62;,
 3;63,58,57;,
 3;64,58,63;,
 3;60,50,65;,
 3;65,50,59;,
 3;66,61,60;,
 3;67,61,66;,
 3;68,63,62;,
 3;69,64,63;,
 3;69,63,68;,
 3;70,64,69;,
 3;71,60,65;,
 3;66,60,71;,
 3;72,66,71;,
 3;72,67,66;,
 3;73,70,69;,
 3;73,69,68;,
 3;74,35,75;,
 3;76,35,74;,
 3;77,78,32;,
 3;79,78,77;,
 3;79,56,78;,
 3;80,56,79;,
 3;74,75,81;,
 3;81,75,51;,
 3;82,76,74;,
 3;83,76,82;,
 3;84,79,77;,
 3;85,80,79;,
 3;85,79,84;,
 3;86,80,85;,
 3;82,74,87;,
 3;87,74,81;,
 3;88,83,82;,
 3;89,83,88;,
 3;90,85,84;,
 3;91,86,85;,
 3;91,85,90;,
 3;92,86,91;,
 3;88,82,93;,
 3;93,82,87;,
 3;94,88,93;,
 3;94,89,88;,
 3;95,92,91;,
 3;95,91,90;,
 3;96,30,32;,
 3;96,78,56;,
 3;30,96,8;,
 3;5,96,6;,
 3;55,96,56;,
 3;96,55,6;,
 3;78,96,32;,
 3;96,5,8;,
 3;97,27,11;,
 3;27,97,35;,
 3;97,2,1;,
 3;75,97,51;,
 3;97,52,51;,
 3;97,75,35;,
 3;52,97,1;,
 3;2,97,11;;
 
 MeshMaterialList {
  2;
  128;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.300000;0.300000;0.300000;1.000000;;
   1.000000;
   0.500000;0.500000;0.500000;;
   0.500000;0.500000;0.500000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\�����~�J_�z�z_ver1.1\\�����~�J_�z�z_ver1.1\\Texture\\Acc_C.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  141;
  -0.703783;0.058326;0.708016;,
  -0.700410;0.033618;0.712948;,
  -0.491566;0.339641;0.801877;,
  -0.704653;0.082725;0.704714;,
  -0.702687;0.034958;-0.710640;,
  -0.704944;0.080220;-0.704712;,
  0.491592;0.339542;-0.801903;,
  0.704651;0.082708;-0.704718;,
  -0.699438;0.146617;0.699493;,
  -0.694457;0.188332;0.694450;,
  0.699463;0.146611;-0.699469;,
  0.694417;0.188198;-0.694526;,
  -0.672091;0.310998;0.671993;,
  -0.662149;0.351195;0.661983;,
  -0.662309;0.351156;-0.661843;,
  0.661904;0.351061;-0.662299;,
  0.625209;0.467086;0.625256;,
  0.058348;0.703922;0.707877;,
  0.033591;0.700610;0.712753;,
  0.082730;0.704738;0.704628;,
  0.034992;0.702530;-0.710793;,
  0.080240;0.704781;-0.704873;,
  0.339551;-0.491667;-0.801853;,
  0.082656;-0.704669;-0.704706;,
  0.146620;0.699496;0.699434;,
  0.188300;0.694503;0.694413;,
  0.146592;-0.699459;-0.699477;,
  0.188320;-0.694475;-0.694434;,
  0.310992;0.672133;0.671953;,
  0.351218;0.662190;0.661929;,
  0.350967;0.662255;-0.661998;,
  0.351082;-0.662133;-0.662058;,
  0.467095;-0.625341;0.625117;,
  -0.058230;-0.703821;0.707987;,
  -0.033531;-0.700574;0.712791;,
  -0.339481;-0.491672;0.801880;,
  -0.082594;-0.704637;0.704744;,
  -0.035057;-0.702604;-0.710717;,
  -0.058385;0.703843;-0.707952;,
  -0.082750;0.704602;-0.704762;,
  -0.146506;-0.699426;0.699528;,
  -0.188160;-0.694408;0.694546;,
  -0.188333;-0.694451;-0.694455;,
  -0.188324;0.694296;-0.694613;,
  -0.310938;-0.671944;0.672168;,
  -0.351173;-0.661928;0.662215;,
  -0.310906;0.671934;-0.672192;,
  -0.351065;0.662001;-0.662200;,
  -0.467029;0.625216;0.625291;,
  0.703809;-0.058220;0.708000;,
  0.700551;-0.033569;0.712812;,
  0.704693;-0.082613;0.704686;,
  0.702535;-0.035026;-0.710786;,
  0.704792;-0.080293;-0.704855;,
  -0.704755;-0.082769;-0.704606;,
  0.699553;-0.146557;0.699390;,
  0.694609;-0.188309;0.694304;,
  -0.699548;-0.146689;-0.699368;,
  -0.694490;-0.188333;-0.694416;,
  0.672192;-0.310956;0.671911;,
  0.662210;-0.351129;0.661956;,
  -0.671996;-0.310996;-0.672089;,
  -0.661957;-0.351135;-0.662206;,
  -0.625107;-0.466969;0.625445;,
  -0.403584;-0.403595;-0.821116;,
  -0.403455;0.403576;0.821188;,
  -0.703992;0.058027;-0.707833;,
  -0.339643;0.491665;-0.801815;,
  0.703786;0.058290;-0.708016;,
  0.700479;0.033590;-0.712882;,
  0.704863;0.080397;0.704773;,
  0.702686;0.035054;0.710636;,
  0.703953;0.058153;0.707862;,
  0.339648;0.491730;0.801773;,
  -0.699576;0.146557;-0.699367;,
  -0.694597;0.188257;-0.694330;,
  0.694451;0.188362;0.694448;,
  0.699493;0.146670;0.699427;,
  -0.672233;0.310982;-0.671858;,
  0.671946;0.310886;-0.672189;,
  0.662035;0.351201;0.662093;,
  0.672030;0.311003;0.672051;,
  -0.625346;0.467056;0.625141;,
  0.625022;0.467171;-0.625378;,
  -0.625460;0.467141;-0.624963;,
  0.058068;0.703821;-0.708000;,
  0.058287;-0.703843;-0.707960;,
  0.033588;-0.700589;-0.712774;,
  0.080345;-0.704733;0.704909;,
  0.035125;-0.702476;0.710840;,
  0.058170;-0.703764;0.708048;,
  0.491681;-0.339488;0.801871;,
  0.146545;0.699436;-0.699510;,
  0.188211;0.694497;-0.694443;,
  0.188351;-0.694457;0.694445;,
  0.146678;-0.699387;0.699530;,
  0.310848;0.672153;-0.672000;,
  0.310924;-0.672084;-0.672034;,
  0.351169;-0.662192;0.661953;,
  0.311040;-0.672093;0.671972;,
  0.467125;0.625353;0.625082;,
  0.466865;-0.625334;-0.625296;,
  0.466851;0.625437;-0.625202;,
  -0.058099;-0.703912;-0.707907;,
  -0.491675;-0.339626;-0.801817;,
  -0.033642;0.700593;-0.712768;,
  -0.080308;-0.704873;-0.704773;,
  -0.080296;0.704833;0.704814;,
  -0.034986;0.702638;0.710687;,
  -0.058081;0.703899;0.707921;,
  -0.146607;-0.699513;-0.699419;,
  -0.146670;0.699326;-0.699593;,
  -0.188282;0.694472;0.694449;,
  -0.146587;0.699480;0.699457;,
  -0.310977;-0.671994;-0.672099;,
  -0.351180;-0.661968;-0.662171;,
  -0.310958;0.672040;0.672062;,
  -0.351142;0.662057;0.662102;,
  -0.467281;-0.624991;0.625328;,
  -0.466821;0.625237;-0.625425;,
  -0.467007;-0.625150;-0.625374;,
  0.703808;-0.058134;-0.708008;,
  -0.703876;-0.058362;-0.707921;,
  -0.700511;-0.033666;-0.712848;,
  -0.704798;-0.080307;0.704848;,
  -0.702511;-0.035024;0.710811;,
  -0.703813;-0.058103;0.708005;,
  0.699497;-0.146550;-0.699448;,
  0.694470;-0.188287;-0.694449;,
  -0.694437;-0.188287;0.694482;,
  -0.699468;-0.146592;0.699468;,
  0.671973;-0.311049;-0.672087;,
  0.661907;-0.351302;-0.662168;,
  -0.661936;-0.351139;0.662225;,
  -0.671971;-0.310931;0.672143;,
  0.625363;-0.467026;0.625147;,
  -0.625073;-0.467111;-0.625373;,
  0.625058;-0.467190;-0.625329;,
  0.262341;0.538136;-0.800991;,
  0.700473;-0.035529;-0.712794;,
  0.403637;-0.403482;0.821145;;
  128;
  3;0,2,1;,
  3;3,2,0;,
  3;66,4,67;,
  3;5,4,66;,
  3;68,6,69;,
  3;7,6,68;,
  3;70,71,72;,
  3;72,71,73;,
  3;8,3,0;,
  3;9,3,8;,
  3;74,5,66;,
  3;10,7,68;,
  3;75,5,74;,
  3;11,7,10;,
  3;76,70,77;,
  3;77,70,72;,
  3;12,9,8;,
  3;13,9,12;,
  3;78,75,74;,
  3;14,75,78;,
  3;79,11,10;,
  3;15,11,79;,
  3;80,76,81;,
  3;81,76,77;,
  3;16,80,81;,
  3;82,13,12;,
  3;83,15,79;,
  3;84,14,78;,
  3;17,73,18;,
  3;19,73,17;,
  3;85,20,6;,
  3;21,20,85;,
  3;86,22,87;,
  3;23,22,86;,
  3;88,89,90;,
  3;90,89,91;,
  3;24,19,17;,
  3;25,19,24;,
  3;92,21,85;,
  3;26,23,86;,
  3;93,21,92;,
  3;27,23,26;,
  3;94,88,95;,
  3;95,88,90;,
  3;28,25,24;,
  3;29,25,28;,
  3;96,93,92;,
  3;30,93,96;,
  3;97,27,26;,
  3;31,27,97;,
  3;98,94,99;,
  3;99,94,95;,
  3;32,98,99;,
  3;100,29,28;,
  3;101,31,97;,
  3;102,30,96;,
  3;33,35,34;,
  3;36,35,33;,
  3;103,37,104;,
  3;38,67,105;,
  3;106,37,103;,
  3;39,67,38;,
  3;107,108,109;,
  3;109,108,2;,
  3;40,36,33;,
  3;41,36,40;,
  3;110,106,103;,
  3;42,106,110;,
  3;111,39,38;,
  3;43,39,111;,
  3;112,107,113;,
  3;113,107,109;,
  3;44,41,40;,
  3;45,41,44;,
  3;114,42,110;,
  3;46,43,111;,
  3;115,42,114;,
  3;47,43,46;,
  3;116,112,113;,
  3;117,112,116;,
  3;48,117,116;,
  3;118,45,44;,
  3;119,47,46;,
  3;120,115,114;,
  3;49,91,50;,
  3;51,91,49;,
  3;121,52,22;,
  3;53,52,121;,
  3;122,104,123;,
  3;54,104,122;,
  3;124,125,126;,
  3;126,125,35;,
  3;55,51,49;,
  3;56,51,55;,
  3;127,53,121;,
  3;57,54,122;,
  3;128,53,127;,
  3;58,54,57;,
  3;129,124,130;,
  3;130,124,126;,
  3;59,56,55;,
  3;60,56,59;,
  3;131,128,127;,
  3;61,58,57;,
  3;132,128,131;,
  3;62,58,61;,
  3;133,129,134;,
  3;134,129,130;,
  3;63,133,134;,
  3;135,60,59;,
  3;136,62,61;,
  3;137,132,131;,
  3;64,87,22;,
  3;64,123,104;,
  3;20,138,6;,
  3;4,64,67;,
  3;37,64,104;,
  3;138,105,67;,
  3;52,139,22;,
  3;138,69,6;,
  3;65,18,73;,
  3;89,140,91;,
  3;65,1,2;,
  3;125,65,35;,
  3;140,34,35;,
  3;140,50,91;,
  3;108,65,2;,
  3;71,140,73;;
 }
 MeshTextureCoords {
  98;
  0.548090;0.673610;,
  0.557820;0.684540;,
  0.548090;0.686000;,
  0.556980;0.672720;,
  0.438850;0.672690;,
  0.447860;0.686000;,
  0.438130;0.684600;,
  0.447860;0.673610;,
  0.457600;0.684540;,
  0.456760;0.672720;,
  0.539070;0.672690;,
  0.538350;0.684600;,
  0.548090;0.663510;,
  0.554960;0.662380;,
  0.441050;0.662270;,
  0.447860;0.663520;,
  0.454740;0.662380;,
  0.541270;0.662270;,
  0.548120;0.656630;,
  0.551800;0.655550;,
  0.444410;0.655500;,
  0.447900;0.656630;,
  0.451570;0.655550;,
  0.544630;0.655490;,
  0.548220;0.652290;,
  0.448000;0.652290;,
  0.527430;0.694330;,
  0.539810;0.694330;,
  0.526530;0.685440;,
  0.469500;0.685260;,
  0.456200;0.694270;,
  0.468580;0.694270;,
  0.457660;0.704010;,
  0.469480;0.703170;,
  0.526510;0.703350;,
  0.538420;0.704070;,
  0.517330;0.694330;,
  0.516190;0.687460;,
  0.479930;0.687460;,
  0.478680;0.694270;,
  0.479820;0.701150;,
  0.516080;0.701150;,
  0.510440;0.694300;,
  0.509360;0.690630;,
  0.486700;0.690820;,
  0.485570;0.694300;,
  0.486650;0.697980;,
  0.509310;0.697790;,
  0.506100;0.694200;,
  0.489910;0.694410;,
  0.568810;0.694270;,
  0.557880;0.704010;,
  0.556420;0.694270;,
  0.569700;0.703170;,
  0.426290;0.703350;,
  0.439590;0.694330;,
  0.438190;0.704070;,
  0.427210;0.694340;,
  0.426310;0.685440;,
  0.569730;0.685260;,
  0.578910;0.694270;,
  0.580040;0.701150;,
  0.415860;0.701150;,
  0.417110;0.694340;,
  0.415970;0.687460;,
  0.580160;0.687460;,
  0.585790;0.694310;,
  0.586870;0.697980;,
  0.409090;0.697790;,
  0.410220;0.694300;,
  0.409140;0.690630;,
  0.586930;0.690820;,
  0.590140;0.694410;,
  0.405880;0.694200;,
  0.548150;0.714990;,
  0.548150;0.702610;,
  0.539250;0.715890;,
  0.456940;0.715910;,
  0.447930;0.702610;,
  0.447930;0.714990;,
  0.439030;0.715890;,
  0.557160;0.715910;,
  0.548150;0.725090;,
  0.541270;0.726230;,
  0.454740;0.726340;,
  0.447930;0.725090;,
  0.441050;0.726220;,
  0.554960;0.726340;,
  0.548120;0.731980;,
  0.544440;0.733060;,
  0.451380;0.733110;,
  0.447890;0.731970;,
  0.444220;0.733060;,
  0.551600;0.733110;,
  0.548010;0.736320;,
  0.447790;0.736320;,
  0.447890;0.694300;,
  0.548120;0.694300;;
 }
}
