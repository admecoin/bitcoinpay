package=tor
$(package)_version=0.4.0.5
$(package)_download_path=https://dist.torproject.org
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=b5a2cbf0dcd3f1df2675dbd5ec10bbe6f8ae995c41b68cebe2bc95bffc90696e
$(package)_dependencies=zlib libevent openssl
$(package)_patches=remove_libcap.patch

define $(package)_set_vars
  $(package)_config_opts=--disable-asciidoc --disable-tool-name-check --disable-seccomp --with-openssl-dir=$(host_prefix)/etc/openssl
endef

define $(package)_preprocess_cmds
  patch -p1 < $($(package)_patch_dir)/remove_libcap.patch
endef

define $(package)_config_cmds
  $($(package)_autoconf)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install && \
  mkdir -p $($(package)_staging_prefix_dir)/lib && \
  cp $($(package)_build_dir)/src/core/libtor-app.a $($(package)_staging_prefix_dir)/lib/libtor-app.a && \
  cp $($(package)_build_dir)/src/lib/libtor-ctime.a $($(package)_staging_prefix_dir)/lib/libtor-ctime.a && \
  cp $($(package)_build_dir)/src/lib/libtor-crypt-ops.a $($(package)_staging_prefix_dir)/lib/libtor-crypt-ops.a && \
  cp $($(package)_build_dir)/src/lib/libcurve25519_donna.a $($(package)_staging_prefix_dir)/lib/libcurve25519_donna.a && \
  cp $($(package)_build_dir)/src/trunnel/libor-trunnel.a $($(package)_staging_prefix_dir)/lib/libor-trunnel.a && \
  cp $($(package)_build_dir)/src/ext/ed25519/donna/libed25519_donna.a $($(package)_staging_prefix_dir)/lib/libed25519_donna.a && \
  cp $($(package)_build_dir)/src/ext/ed25519/ref10/libed25519_ref10.a $($(package)_staging_prefix_dir)/lib/libed25519_ref10.a && \
  cp $($(package)_build_dir)/src/ext/keccak-tiny/libkeccak-tiny.a $($(package)_staging_prefix_dir)/lib/libkeccak-tiny.a
endef

define $(package)_postprocess_cmds
endef

