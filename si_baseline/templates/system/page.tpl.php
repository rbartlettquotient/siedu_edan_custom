<?php
if (isset($_GET['dpm-page'])) {
  dpm($variables);
}

?>
<div<?php print $attributes; ?>>
  <?php if ($page['colorbox'] == FALSE): ?>
    <a id="main"></a>
    <header class="l-header <?php print !empty($page['header_preface_left']) ? 'has-preface-left' : ''; ?>" role="banner">
      <?php if (!empty($page['header_preface_left']) || !empty($page['header_preface_right'])): ?>
        <div class="l-header-preface-wrapper">
          <div class="l-container">
              <?php print render($page['header_preface_left']); ?>
              <?php print render($page['header_preface_right']); ?>

          </div>
        </div>
      <?php endif; ?>
      <div class="l-header-inner l-container">
        <div class="l-branding">
          <?php if ($logo): ?>
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="site-logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
          <?php endif; ?>

          <?php if ($site_name || $site_slogan): ?>
            <?php if ($site_name): ?>
              <div class="site-name">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </div>
            <?php endif; ?>

            <?php if ($site_slogan): ?>
              <h2 class="site-slogan"><?php print $site_slogan; ?></h2>
            <?php endif; ?>
          <?php endif; ?>

          <?php print render($page['branding']); ?>
        </div>
        <?php print render($page['header']); ?>
      </div>
      <?php if($page['navigation']): ?>
        <div class="l-navigation">
          <?php print render($page['navigation']); ?>
        </div>
      <?php endif; ?>
    </header>
  <?php endif; ?>
    <div class="l-content-wrapper">
      <?php print render($page['highlighted']); ?>
      <a id="main-content"></a>
      <div class="l-main clearfix" role="main">
        <?php print render($title_prefix); ?>
        <?php print render($title_suffix); ?>
        <?php print $messages; ?>
        <?php print render($tabs); ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>
        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
      </div>

      <?php print render($page['sidebar_first']); ?>
      <?php print render($page['sidebar_second']); ?>
    </div>

  <?php if ($page['colorbox'] == FALSE): ?>
  <footer class="l-footer" role="contentinfo">
    <?php print render($page['footer']); ?>
  </footer>
  <div class="region--postscript">
    <div>
      <a href="#main" class="page-nav"><span class="icon"></span><span class="text">Back to Top</span> </a>
    </div>
  </div>
</div>
<?php endif; ?>
<?php
//if(isset($GLOBALS['SI_PAGE_START'])) {
//  $end = microtime(TRUE);
//  $GLOBALS['EDAN_TEST']['page_load'] = $end - $GLOBALS['SI_PAGE_START'];
//}
//dpm($GLOBALS['EDAN_TEST']);

?>

