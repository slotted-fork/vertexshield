{
  description = "VertexShield";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
  };
  outputs = { self, nixpkgs, flake-utils }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};

      version = "0.1.0";

      nativeBuildInputs = with pkgs; [
        makeWrapper
        pkg-config
      ];

      buildInputs = with pkgs; [
        raylib
      ];
    in
      {
        packages.${system}.default = pkgs.stdenv.mkDerivation {
          inherit buildInputs nativeBuildInputs version;

          pname = "vertexshield";

          src = ./src;

          buildPhase = "make";

          installPhase = ''
            runHook preInstall
            install -m755 -Dt $out/bin/ vertexshield
            runHook postInstall
          '';

          postInstall = ''
            wrapProgram $out/bin/vertexshield \
              --prefix LD_LIBRARY_PATH : ${pkgs.lib.makeLibraryPath buildInputs}
          '';
        };

        devShells.${system}.default = pkgs.mkShell {
          inherit buildInputs nativeBuildInputs version;

          packages = with pkgs; [ ccls ];
        };
      };
}
