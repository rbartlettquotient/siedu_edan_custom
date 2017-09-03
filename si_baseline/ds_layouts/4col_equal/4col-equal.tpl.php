<?php

  /**
   * @file
   * Display Suite fluid 2 column stacked template.
   */
  $first_classes .= 'col col-first col-sm-6 col-md-3';
  $second_classes .= 'col col-second col-sm-6 col-md-3';
  $third_classes .= 'col col-third col-sm-6 col-md-3';
  $fourth_classes .= 'col col-fourth col-sm-6 col-md-3 last';

//  dpm($variables);
?>
<<?php print $layout_wrapper;
  print $layout_attributes; ?> class="layout four-column <?php print $classes;?> ">
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

<?php if ($first): ?>
  <<?php print $first_wrapper ?> class="<?php print $first_classes; ?>">
    <div class="inner">
      <?php print $first; ?>
    </div>
  </<?php print $first_wrapper ?>>
<?php endif; ?>
<?php if ($second): ?>
  <<?php print $second_wrapper ?> class="<?php print $second_classes; ?>">
  <div class="inner">
    <?php print $second; ?>
  </div>
  </<?php print $second_wrapper ?>>
<?php endif; ?>
<?php if ($third): ?>
  <<?php print $third_wrapper ?> class="<?php print $third_classes; ?>">
  <div class="inner">
    <?php print $third; ?>
  </div>

  </<?php print $third_wrapper ?>>
<?php endif; ?>
<?php if ($fourth): ?>
  <<?php print $fourth_wrapper ?> class="<?php print $fourth_classes; ?>">
  <div class="inner">
    <?php print $fourth; ?>
  </div>

  </<?php print $fourth_wrapper ?>>
<?php endif; ?>
</div>
</<?php print $layout_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
