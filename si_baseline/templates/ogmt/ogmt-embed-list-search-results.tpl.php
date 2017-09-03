<?php dpm($variables);
libraries_load('imagesloaded');
libraries_load('masonry');
?>
<div class="masonry-grid-wrapper">
  <ul class="reset-list masonry-grid hover-title">
    <?php dpm($docs); foreach ($docs as $doc):
      if(isset($doc['#title_link']) && !empty($doc['#title_link'])) {
        $url = url($doc['#title_link']['path'], array('query' => $doc['#title_link']['query'], 'fragment' => $doc['#title_link']['fragment']));
      }
      $keys = array_keys($doc['siedu_media']);
      $key = $keys[0];
      $siedu_media = $doc['siedu_media'][$key];
      ?>
      <li class="item col-sm-6 col-sm-4 col-md-3">
        <div class="node--teaser node--teaser-long">

          <a href="<?php print isset($url) ? $url : '#';?>" class="inner<?php !isset($url) ? ' prevent-link': '' ?>">

            <?php if (!empty($siedu_media)): ?>
              <div class="b-media-wrapper field--type-image">
                <img src="<?php print $siedu_media['extended']['medium_size']; ?>" />
               </div>
            <?php endif; ?>
            <div class="b-text-wrapper">
              <h3 class="title delta"><?php echo $doc['#title_plain']; ?></h3>
            </div>
          </a>
        </div>
      </li>
    <?php endforeach; ?>
  </ul>
</div>
