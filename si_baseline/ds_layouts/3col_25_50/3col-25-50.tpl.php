<?php

  /**
   * @file
   * Display Suite fluid 2 column stacked template.
   */
  if ($left && $right) {
    $left_classes .= 'col col-first col-sm-6 col-md-3';
    $middle_classes .= 'col col-second col-sm-6 col-md-3 last-sm';
    $right_classes .= 'col col-third col-md-6 last-md';
  } elseif ($left || $right) {
    $left_classes .= 'col col-first col-sm-6';
    $middle_classes .= 'col col-second col-sm-6';
    $right_classes .= 'col-third col-sm-6 last-sm';
  }
  //  dpm($variables);
?>
<<?php print $layout_wrapper;
  print $layout_attributes; ?> class="grid-wrapper <?php print $classes; ?> cf">

<?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
<?php endif; ?>
<?php if ($header): ?>
  <<?php print $header_wrapper ?> class="group-header<?php print $header_classes; ?>">
  <div class="header-theme"></div>
  <?php print $header; ?>
  </<?php print $header_wrapper ?>>
<?php endif; ?>
<div class="content">
  <?php if ($left): ?>
  <<?php print $left_wrapper ?> class="<?php print $left_classes; ?>">
  <div class="inner">
    <?php print $left; ?>
  </div>
</<?php print $left_wrapper ?>>
<?php endif; ?>
<?php if ($middle): ?>
  <<?php print $middle_wrapper ?> class="<?php print $middle_classes; ?>">
  <div class="inner">
    <?php print $middle; ?>
  </div>

  </<?php print $middle_wrapper ?>>
<?php endif; ?>
<?php if ($right): ?>
  <<?php print $right_wrapper ?> class="<?php print $right_classes; ?>">
  <div class="inner">
    <?php print $right; ?>
  </div>

  </<?php print $right_wrapper ?>>
<?php endif; ?>
</div>
</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
