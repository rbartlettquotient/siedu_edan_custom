<?php
//dpm($variables);
//dpm(json_decode($variables['raw_json']));
//dpm($variables['object_group_page_object']);
?>
<div class="wrapper--ogmt">
  <?php if ($unit_link): ?>
  <div class="bg-gray-light bg wrapper--si-unit">
    <div class="inside l-container">
        <div class="<?php print $unit_class;?>">
          <?php print $unit_link; ?></div>
    </div>
  </div>
  <?php endif; ?>
  <div class="pane-page-header l-container">
    <div class="row-1 has-other-content">
      <h1 class="page-title has-share-buttons">
        <?php if ($parent_title): ?>
          <span><?php print $parent_title; ?></span>
        <?php endif; ?>
        <?php print $title; ?>
      </h1>
    </div>

      <div class="row-2 wrapper--preface-buttons">

        <div class="link-wrapper">
          <?php if($back_link): 		?>
            <div class="back-link"><?php echo $back_link; ?></div>
          <?php endif; ?>
          <?php
          $block = module_invoke('addthis', 'block_view', 'addthis_block');
          echo render($block['content']);
          ?>
        </div>
      </div>

  </div>

  <div class="content-wrapper-ogmt layout l-container">
    <div class="l-region--main-content col edan-content <?php print $menu ? 'col-sm-9 col-md-9' : 'col-12' ?>">
      <?php if($is_external && !empty($rendered_feature)): ?>
        <div class="field--type-image left">
          <?php print $rendered_feature ?>
        </div>
      <?php endif; ?>
      <?php print $content; ?>
    </div>
    <?php if ($menu && !empty($menu_array)): ?>
      <div class="l-region--left-aside col col-sm-3 col-md-3 last">
        <div class="side-nav">

          <div class="ogmt-og-menu">
            <ul class="menu sf-menu">
              <?php foreach ($menu_array as $menu_item): ?>
                <li><a href="<?php print $menu_item['link']; ?>" <?php print drupal_attributes($menu_item['attributes']); ?>><?php print t($menu_item['title']); ?></a></li>
              <?php endforeach; ?>
            </ul>
          </div>

        </div>
      </div>
    <?php endif; ?>
  </div>




  <?php /*render($node->field_mycustomfield);*/ ?>

  <?php if ($search_results): ?>
    <div class="l-container-wide">
      <?php print $search_results; ?>
    </div>
  <?php endif; ?>
</div>
